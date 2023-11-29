# 1. creating the executables
cd exct
g++ ../brute.cpp -fsanitize=address -fsanitize-address-use-after-scope -o brute_executable
g++ ../optimal.cpp -fsanitize=address -fsanitize-address-use-after-scope  -o optimal_executable

# 2. getting the number of times to run the script from command line args
n=$1

# --------------------- 3 -------------------------- #
# running loop for n times (N files)
for (( i=1; i<=n; ++i ))
do
  # generate and map testcases to testcase.txt
  python3 ../testcase.py 
  start1=$(date +%s.%N)
  ./brute_executable < testcase.txt > brute_out.txt
  end1=$(date +%s.%N)
  #/usr/bin/time -v ./brute_executable < testcase.txt > brute_out.txt
  

  

  start2=$(date +%s.%N)
  ./optimal_executable < testcase.txt > optimal_out.txt
  end2=$(date +%s.%N)  
  #/usr/bin/time -v ./optimal_executable < testcase.txt > optimal_out.txt
   

# Bash Magic : If the difference command produces any output
  if [[ $(diff brute_out.txt optimal_out.txt) ]]
  then
    # map the output of diff command to difference_file
    echo "$(diff -Z brute_out.txt optimal_out.txt)" > difference_file.txt

    echo "Difference reported in file difference_file.txt"
    echo "-----------------------------------------------"
    echo "You Can find the testcase where your optimal solution failed in testcase.txt"
    echo "and their respective outputs in brute_out.txt and optimal_out.txt"
    
    # Once the difference is found and we've reported it 
    # then no need to generate extra testcases we can break right here
    break
  else
    runtime1=$(python3 -c "print('{:3.6f}'.format(${end1} - ${start1}))")
    runtime2=$(python3 -c "print('{:3.6f}'.format(${end2} - ${start2}))")
    test_cnt=$(python3 -c "print('{:3d}'.format(${i}))")
    echo "AC on super-test $test_cnt | brute_time: $runtime1 | optimal_time: $runtime2"
  fi
done

# When the program passes all the test files
echo "--------------Testing done-----------"