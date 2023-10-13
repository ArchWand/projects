bin/out: src/*.cpp
	g++ src/*.cpp -Wall -Wextra -o bin/out -g

.PHONY: edit edit0 run npooteam npooplayer npoocustom smallteam smallplayer smallcustom ecacteam ecacplayer ecaccustom 2012team 2012player 2012custom 2011team 2011player 2011custom diff all gdb clean

edit:
	nvim src/main.cpp

run: bin/out
	bin/out data/no_penalties_or_overtime.txt out/player/no_penalties_or_overtime_output.txt --player_stats

clean:
	rm -f bin/out

gdb: bin/out
	echo "r data/no_penalties_or_overtime.txt out/player/no_penalties_or_overtime_output.txt --player_stats" | xsel -b
	gdb bin/out --tui

npooteam: bin/out
	bin/out data/no_penalties_or_overtime.txt out/team/no_penalties_or_overtime_output.txt --team_stats

npooplayer: bin/out
	bin/out data/no_penalties_or_overtime.txt out/no_penalties_or_overtime_output.txt --player_stats

npoocustom: bin/out
	bin/out data/no_penalties_or_overtime.txt out/no_penalties_or_overtime_output.txt --custom_stats

smallteam: bin/out
	bin/out data/2012_small.txt out/team/2012_small_output.txt --team_stats

smallplayer: bin/out
	bin/out data/2012_small.txt out/player/2012_small_output.txt --player_stats

smallcustom: bin/out
	bin/out data/2012_small.txt out/custom/2012_small_output.txt --custom_stats

ecacteam: bin/out
	bin/out data/2012_ecac.txt out/team/2012_ecac_output.txt --team_stats

ecacplayer: bin/out
	bin/out data/2012_ecac.txt out/player/2012_ecac_output.txt --player_stats

ecaccustom: bin/out
	bin/out data/2012_ecac.txt out/custom/2012_ecac_output.txt --custom_stats

2012team: bin/out
	bin/out data/2012_all.txt out/team/2012_all_output.txt --team_stats

2012player: bin/out
	bin/out data/2012_all.txt out/player/2012_all_output.txt --player_stats

2012custom: bin/out
	bin/out data/2012_all.txt out/custom/2012_all_output.txt --custom_stats

2011team: bin/out
	bin/out data/2011_all.txt out/team/2011_all_output.txt --team_stats

2011player: bin/out
	bin/out data/2011_all.txt out/player/2011_all_output.txt --player_stats

2011custom: bin/out
	bin/out data/2011_all.txt out/custom/2011_all_output.txt --custom_stats

all: bin/out
	bin/out data/no_penalties_or_overtime.txt out/team/no_penalties_or_overtime_output.txt --team_stats
	bin/out data/no_penalties_or_overtime.txt out/player/no_penalties_or_overtime_output.txt --player_stats
	bin/out data/no_penalties_or_overtime.txt out/custom/no_penalties_or_overtime_output.txt --custom_stats
	bin/out data/2012_small.txt out/team/2012_small_output.txt --team_stats
	bin/out data/2012_small.txt out/player/2012_small_output.txt --player_stats
	bin/out data/2012_small.txt out/custom/2012_small_output.txt --custom_stats
	bin/out data/2012_ecac.txt out/team/2012_ecac_output.txt --team_stats
	bin/out data/2012_ecac.txt out/player/2012_ecac_output.txt --player_stats
	bin/out data/2012_ecac.txt out/custom/2012_ecac_output.txt --custom_stats

diff: bin/out all
	cat out/team/no_penalties_or_overtime_output.txt > out/diff/no_penalties_or_overtime_output.txt
	cat out/player/no_penalties_or_overtime_output.txt >> out/diff/no_penalties_or_overtime_output.txt
	diff out/diff/no_penalties_or_overtime_output.txt examples/no_penalties_or_overtime_output.txt
	cat out/team/2012_small_output.txt > out/diff/2012_small_output.txt
	cat out/player/2012_small_output.txt >> out/diff/2012_small_output.txt
	diff out/diff/2012_small_output.txt examples/2012_small_output.txt
	cat out/team/2012_ecac_output.txt > out/diff/2012_ecac_output.txt
	cat out/player/2012_ecac_output.txt >> out/diff/2012_ecac_output.txt
	diff out/diff/2012_ecac_output.txt examples/2012_ecac_output.txt

