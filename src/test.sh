#bin/bash

for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/good/*.lat
do
  if ! ./TestLatte -s ${file} > /dev/null; then
    echo ${file} WROOOOOOOOOOOONG
  fi
done

for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/extensions/arrays1/*.lat
do
  if ! ./TestLatte -s ${file} > /dev/null; then
    echo ${file} WROOOOOOOOOOOONG
  fi
done

for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/extensions/struct/*.lat
do
  if ! ./TestLatte -s ${file} > /dev/null; then
    echo ${file} WROOOOOOOOOOOONG
  fi
done

for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/extensions/objects1/*.lat
do
  if ! ./TestLatte -s ${file} > /dev/null; then
    echo ${file} WROOOOOOOOOOOONG
  fi
done

for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/extensions/objects2/*.lat
do
  if ! ./TestLatte -s ${file} > /dev/null; then
    echo ${file} WROOOOOOOOOOOONG
  fi
done

#for file in /home/adrian/CLionProjects/compilator/lattests201003/lattests/bad/*.lat
#do
#  if ./TestLatte -s ${file} > /dev/null; then
#    echo ${file} WROOOOOOOOOOOONG
#  fi
#done

