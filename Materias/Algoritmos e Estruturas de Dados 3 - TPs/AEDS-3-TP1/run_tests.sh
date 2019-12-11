#! /bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <memory-KB>"
    exit 1
fi

mem=$1

exe="./tp1"
tests="testes"
results="resultados"

fails=""

for f in ${tests}/*.txt; do
    base=`basename ${f}`
    ${exe} "${f}" "${results}/${base}.out" ${mem}
    ret_exe=$?

    diff ${results}/${base}.out ${tests}/${base}.out
    ret_diff=$?

    if [ ${ret_exe} -ne 0 ] || [ ${ret_diff} -ne 0 ]; then
            fails="${fails} ${f}"
    fi
done

echo ""
echo ""
echo "=---------------------------------------------------------------------="
echo "=-------------------------- RESULTADOS -------------------------------="
echo "=---------------------------------------------------------------------="

if [ -z "${fails}" ]; then
    echo "SUCESSO!!"
else
    echo "Falharam:"
    for f in ${fails}; do
        echo -e "\t${f}"
    done
fi

echo "=---------------------------------------------------------------------="
