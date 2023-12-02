file_name=$1
bin_name=program.exe

if [ -z "$file_name" ]
then
  echo "Error: You must provide a .c file as a parameter"
  exit 1
fi

echo "Compiling..."
gcc $file_name -O3 -mavx512f -mavx512er -mavx512cd -mavx512pf -fopenmp -o $bin_name

if [ "$?" -ne "0" ]; then
  echo "Compilation error, check your code."
  exit 1
fi

for n in 2000 4000 8000 16000; do
  echo "Running with N = $n"
  for i in 1 4 16 64; do
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