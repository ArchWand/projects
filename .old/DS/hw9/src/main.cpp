#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int hash(const std::string& string, int start, int len, int &table_size) {
	int hash = 0;
	for (int i = start; i < start + len; i++) {
		hash *= 4;
		switch (string[i]) {
			case 'A': hash += 0; break;
			case 'C': hash += 1; break;
			case 'G': hash += 2; break;
			case 'T': hash += 3; break;
		}
	}
	return hash % table_size;
}

void read_genome(std::string& genome_string, const std::string& filename) {
	std::ifstream genome_file(filename);
	std::string line;
	genome_string = "";

	while (genome_file >> line) {
		genome_string += line;
	}
	genome_file.close();
}

void resize_table(const std::string& data, std::vector<int> *&genome,
		int &table_size, int &occupied, int k) {
	int new_table_size = table_size * 2;
	std::vector<int> *new_genome = new std::vector<int>[new_table_size];
	occupied = 0;

	for (int j = 0; j < table_size; j++) {
		for (unsigned l = 0; l < genome[j].size(); l++) {
			int hash_value = hash(data, genome[j][l], k, new_table_size);
			if (genome[hash_value].size() == 0) { occupied++; }
			new_genome[hash_value].push_back(genome[j][l]);
		}
	}

	delete[] genome;
	genome = new_genome;
	table_size = new_table_size;
}

void find_kmers( const std::string& data, std::vector<int> *&genome,
		int &table_size, int k, float occupancy) {
	int occupied = 0;

	for (unsigned i = 0; i < data.size() - k; i++) {
		int hash_value = hash(data, i, k, table_size);
		if (genome[hash_value].size() == 0) { occupied++; }
		genome[hash_value].push_back(i);

		if (occupied > table_size * occupancy) {
			resize_table(data, genome, table_size, occupied, k);
		}
	}
}

void query( const std::string& genome_string, const std::vector<int> *genome,
		int &table_size, const std::string& query, int k, int mismatch) {
	const std::vector<int>& possible = genome[hash(query, 0, k, table_size)];
	bool found = false;

	for (unsigned i = 0; i < possible.size(); i++) {
		int mismatches = 0;
		bool is_kmer = true;
		for (int j = 0; j < k; j++) {
			if (query[j] != genome_string[possible[i] + j]) {
				is_kmer = false;
				break;
			}
		}
		if (!is_kmer) { continue; }

		for (unsigned j = k; j < query.size(); j++) {
			if (query[j] != genome_string[possible[i] + j]) {
				mismatches++;
				if (mismatches > mismatch) { break; }
			}
		}

		if (mismatches > mismatch) { continue; }
		found = true;
		std::cout << possible[i] << " " << mismatches << " " <<
			genome_string.substr(possible[i], query.size()) << std::endl;
	}

	if (!found) {
		std::cout << "No Match" << std::endl;
	}
}

int main(int argc, char *argv[]) {
	std::vector<int> *genome = new std::vector<int>[100];
	std::string genome_string;
	int table_size = 100;
	float occupancy = 0.5;
	int k = 0;

	std::string line;
	while (std::cin >> line) {
		// Commands sorted in order of approximate frequency
		if (line == "query") {
			int mismatch;
			std::cin >> mismatch >> line;
			std::cout << "Query: " << line << std::endl;
			query( genome_string, genome, table_size, line, k, mismatch);
		} else if (line == "kmer") {
			std::cin >> k;
			find_kmers( genome_string, genome, table_size, k, occupancy);
		} else if (line == "quit") {
			break;
		} else if (line == "genome") {
			std::cin >> line;
			read_genome(genome_string, line);
		} else if (line == "table_size") {
			std::cin >> table_size;
			delete[] genome;
			genome = new std::vector<int>[table_size];
		} else if (line == "occupancy") {
			std::cin >> occupancy;
		}
	}
	return 0;
}
