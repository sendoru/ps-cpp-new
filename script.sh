python tc_gen.py > tc.txt
g++ source/main.cpp -o main.out
cat tc.txt | ./main.out > output.txt
python test.py