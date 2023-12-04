file_name=$1
bin_name=program.exe

if [ -z "$file_name" ]
then
  echo "Error: You must provide a .c file as a parameter"
  exit 1
fi

echo "Compiling..."
g++ $file_name -O3 -fopenmp -o $bin_name

echo "Setting env variables"
export KMP_AFFINITY=scatter
export KMP_PLACE_THREADS=64c,1t


if [ "$?" -ne "0" ]; then
  echo "Compilation error, check your code."
  exit 1
fi

for n in 2000 4000 8000 16000; do
  echo "Running with N = $n"
  for i in 16 64; do
    echo "Running with $i threads"
    export OMP_NUM_THREADS=$i
    echo "-----------------------------------"
    for j in $(seq 1 3); do
      ./$bin_name $n
      if [ "$?" -ne "0" ]; then
        echo "Execution error, check your code."
        exit 1
      fi
    done
    echo "-----------------------------------"
  done
done

[ -e $bin_name ] && rm $bin_name

echo "Success!"