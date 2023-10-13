#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>


// ===== Custom Types =====

struct Team {
	std::string name;
	int wins;
	int losses;
	int ties;
	int goals;
	int penalties;

	Team(const std::string name)
		: name(name), wins(0), losses(0), ties(0), goals(0), penalties(0) {}
	// Assignment operator for Team
	Team& operator=(const Team& rhs) {
		name = rhs.name;
		wins = rhs.wins;
		losses = rhs.losses;
		ties = rhs.ties;
		goals = rhs.goals;
		penalties = rhs.penalties;
		return *this;
	}

	int total_games() const { return wins + losses + ties; }
	float win_percentage() const { return (wins + 0.5*ties) / total_games(); }
};

struct Player {
	std::string name;
	std::string team;
	int goals;
	int assists;
	int penalties;

	Player(const std::string name, const std::string team)
		: name(name), team(team), goals(0), assists(0), penalties(0) {}
	// Assignment operator for Player
	Player& operator=(const Player& rhs) {
		name = rhs.name;
		team = rhs.team;
		goals = rhs.goals;
		assists = rhs.assists;
		penalties = rhs.penalties;
		return *this;
	}
};

// Comparison operator for Team
bool operator<(const Team& lhs, const Team& rhs) {
	// Sort by win percentage, then total goals, then lexographically
	if (lhs.win_percentage() != rhs.win_percentage()) {
		return lhs.win_percentage() > rhs.win_percentage();
	} else if (lhs.goals != rhs.goals) {
		return lhs.goals > rhs.goals;
	} else {
		return lhs.name < rhs.name;
	}
}

// Comparison operator for Player
bool operator<(const Player& lhs, const Player& rhs) {
	// Sort by goals + assists, then lower penalties, then lexographically
	if (lhs.goals + lhs.assists != rhs.goals + rhs.assists) {
		return lhs.goals + lhs.assists > rhs.goals + rhs.assists;
	} else if (lhs.penalties != rhs.penalties) {
		return lhs.penalties < rhs.penalties;
	} else {
		return lhs.name < rhs.name;
	}
}

// Equality operator for Player (used for linear search)
bool operator==(const Player& lhs, const Player& rhs) {
	return lhs.name == rhs.name && lhs.team == rhs.team;
}

// Enum to distinguish between goals and penalties
enum Action{GOAL, PENALTY};


// ===== Utility Functions =====

// If we see a day of the week in the file, then it must be the
// start of a new game
bool is_day_of_week(const std::string &day) {
	return day == "Monday," || day == "Tuesday," || day == "Wednesday," ||
		day == "Thursday," || day == "Friday," || day == "Saturday," ||
		day == "Sunday,";
}

// Period headers are used to indicate the start of a new period
bool is_period_header(const std::string &period) {
	return period == "PERIOD";
}

// Overtime headers are essentially the same as period headers
bool is_overtime_header(const std::string &overtime) {
	return overtime == "OVERTIME";
}

// Times are used to indiate either a goal or a penalty
// Within a penalty, times indicate the severity of a penalty
bool is_time(const std::string &time) {
	// It is a time if it contains a color
	for (char c : time) {
		if (c == ':') { return true; }
	}
	return false;
}

// Final headers indicate the end of a game, and the reporting of scores
bool is_final_header(const std::string &final) {
	return final == "FINAL";
}

// Turn a string into an Action
Action get_action(const std::string word) {
	if (word == "goal") {
		return GOAL;
	} else if (word == "penalty") {
		return PENALTY;
	} else {
		std::cerr << "Error: Unknown action " << word << std::endl;
		exit(1);
	}
}

int get_team_index(std::vector<Team> &teams, const std::string &name) {
	for (Team &team : teams) {
		if (team.name == name) {
			return &team - &teams[0];
		}
	}
	teams.push_back(Team(name));
	return teams.size() - 1;
}

int get_player_index(std::vector<Player> &players, const std::string &name, const std::string &team) {
	for (Player &player : players) {
		if (player == Player(name, team)) {
			return &player - &players[0];
		}
	}
	players.push_back(Player(name, team));
	return players.size() - 1;
}


// ===== Parsing Functions =====

// Extrapolating this out makes the main function more readable
void read_file(const std::string &filename,
		std::vector<Team> &teams, std::vector<Player> &players) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file " << filename << std::endl;
		return;
	}

	// Since we cannot depend on the whitespace formatting of the input
	// file, we will use the << operator
	while (file.good()) {
		std::string next;
		file >> next;
		if (is_day_of_week(next)) {
			file >> next >> next >> next; // Skip the date
			file >> next >> next >> next; // Skip the teams
		} else if (is_period_header(next)) {
			file >> next; // Skip the period number
		} else if (is_overtime_header(next)) {
			// Skip overtime
		} else if (is_time(next)) {
			std::string team;
			std::string player;
			file >> team >> next >> player;
			Action action = get_action(next);

			int team_index = get_team_index(teams, team);
			int player_index = get_player_index(players, player, team);

			if (action == GOAL) {
				players[player_index].goals++;

				// Credit the assists
				file >> next;
				assert(next == "(");
				for (file >> next; next != ")"; file >> next) {
					players[get_player_index(players, next, team)].assists++;
				}
			} else if (action == PENALTY) {
				players[player_index].penalties++;
				teams[team_index].penalties++;

				file >> next >> next; // Skip the penalty duration and type
			}
		} else if (is_final_header(next)) {
			file >> next; // Team 1
			int team1_index = get_team_index(teams, next);
			int team1_score;
			file >> team1_score;
			file >> next; // Team 2
			int team2_index = get_team_index(teams, next);
			int team2_score;
			file >> team2_score;

			teams[team1_index].goals += team1_score;
			teams[team2_index].goals += team2_score;

			// Calculate the winner
			if (team1_score > team2_score) {
				teams[team1_index].wins++;
				teams[team2_index].losses++;
			} else if (team2_score > team1_score) {
				teams[team2_index].wins++;
				teams[team1_index].losses++;
			} else {
				teams[team1_index].ties++;
				teams[team2_index].ties++;
			}
		} else if (next == "") {
			// Skip blank lines
		} else {
			std::cerr << "Formatting error: " << next << std::endl;
			exit(1);
		}
	}

	file.close();
}


// ===== Printing Functions =====

void print_team_stats(const std::vector<Team> &unsorted_teams, const std::string &filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file " << filename << std::endl;
		return;
	}

	// Sort the teams
	std::vector<Team> teams = unsorted_teams;
	std::sort(teams.begin(), teams.end());

	// Print the header
	file << std::setw(14) << std::left << "Team Name"
		<< std::setw(4) << std::left << "W"
		<< std::setw(4) << std::left << "L"
		<< std::setw(4) << std::left << "T"
		<< std::setw(4) << "Win%"
		<< std::setw(7) << std::right << "Goals"
		<< std::setw(11) << std::right << "Penalties"
		<< std::endl;

	// Print the teams
	for (Team &team : teams) {
		file << std::setw(14) << std::left << team.name
			<< std::setw(4) << std::left << team.wins
			<< std::setw(4) << std::left << team.losses
			<< std::setw(4) << std::left << team.ties
			<< std::setw(4) << std::fixed << std::setprecision(2) << team.win_percentage()
			<< std::setw(7) << std::right << team.goals
			<< std::setw(11) << std::right << team.penalties
			<< std::endl;
	}
	file << std::endl;
}

void print_player_stats(const std::vector<Player> &unsorted_players, const std::string &filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file " << filename << std::endl;
		return;
	}

	// Sort the players
	std::vector<Player> players = unsorted_players;
	std::sort(players.begin(), players.end());

	// Print the header
	file << std::setw(17) << std::left << "Player Name"
		<< std::setw(13) << std::left << "Team"
		<< std::setw(5) << std::right << "Goals"
		<< std::setw(9) << std::right << "Assists"
		<< std::setw(11) << std::right << "Penalties"
		<< std::endl;

	// Print the players
	for (Player &player : players) {
		file << std::setw(17) << std::left << player.name
			<< std::setw(13) << std::left << player.team
			<< std::setw(5) << std::right << player.goals
			<< std::setw(9) << std::right << player.assists
			<< std::setw(11) << std::right << player.penalties
			<< std::endl;
	}
	file << std::endl;
}


int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0]
			<< " <filename> <output file> <statistic>" << std::endl;
		return 1;
	}

	std::vector<Team> teams;
	std::vector<Player> players;
	read_file(argv[1], teams, players);

	if (std::string(argv[3]) == "--team_stats") {
		print_team_stats(teams, argv[2]);
	} else if (std::string(argv[3]) == "--player_stats") {
		print_player_stats(players, argv[2]);
	} else if (std::string(argv[3]) == "--custom_stats") {
	} else {
		std::cerr << "Error: Unknown statistic " << argv[3] << std::endl;
		return 1;
	}
	return 0;
}

