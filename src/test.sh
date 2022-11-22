#bin/bash

for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/good/*.lat
do
  if ! ./TestLatte -s ${file} > /dev/null; then
    echo ${file} WROOOOOOOOOOOONG
  fi
done

for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/bad/*.lat
do
  if ./TestLatte -s ${file} > /dev/null; then
    echo ${file} WROOOOOOOOOOOONG
  fi
done

