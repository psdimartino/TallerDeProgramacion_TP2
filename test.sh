# #  0    1         2         3   4       5       6
# #  ./tp <targets> <allowed> <w> <index> <pages> <n>

# RED='\033[0;31m'
# BLUE='\033[0;34m'
# NC='\033[0m'
# GREEN='\033[0;32m'
# CYAN='\033[0;36m'
# echo -e "${BLUE}\n#########################################"
# echo -e "~~~~~~~~~~~~~~~~~ Tests ~~~~~~~~~~~~~~~~~"
# echo -e "#########################################\n${NC}"

# rm ./tests/output/*

# tests=("counters" "exact_domain" "incomplete_index" "nested" "scrap_single")
# allowed=("free-counters.co.uk", "sercom.taller-de-programacion.github.io", "taller-de-programacion.github.io" "taller-de-programacion.github.io" "www.savewalterwhite.com")
# for t in ${tests[@]}; do
#     ./tp ./tests/input/$t/target www.savewalterwhite.com 3 ./tests/input/$t/index ./tests/input/$t/pages 1 >> ./tests/output/$t
#     val_return=$?
#     cero=0
#     uno=1
#     diff --color ./tests/expected/$t/__stdout__ ./tests/output/$t
#     dif_return=$?
#     if [ $dif_return == $uno ]
#     then
#         printf "${RED} FAILED: Differences in output ${NC}"
#     else
#         printf "${GREEN} diff OK ${NC}"
#     fi
#     echo
#     # Return results
#     if [ $val_return != $cero ]
#     then
#         printf "${RED} FAILED: Bad return value ${NC}"
#     else
#         printf "${GREEN} return OK ${NC}"
#     fi
#     echo
#     echo -e "\n-------------------------------------\n" 
# done

RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
echo -e "${BLUE}\n#########################################"
echo -e "~~~~~~~~~~~~~~~~~ Tests ~~~~~~~~~~~~~~~~~"
echo -e "#########################################\n${NC}"

for dTest in ./test/*; do
    #OPEN FILES
    expected=$(cat ./expected/${dTest/test/}/__stdout__)
    expected_return=$(cat ./expected/${dTest/test/}/__return_code__)

    echo $dTest
    echo

    #RUN VALGRIND
    $dTest/cmd > ${dTest/test/output}
    val_return=$?
    uno=1

    # Diff results
    diff --color ${dTest/test/output} ./expected/${dTest/test/}/__stdout__
    dif_return=$?
    if [ $dif_return == $uno ]
    then
        printf "${RED} FAILED: Differences in output ${NC}"
    else
        printf "${GREEN} diff OK ${NC}"
    fi
    echo

    # Return results
    if [ $val_return != $expected_return ]
    then
        printf "${RED} FAILED: Bad return value ${NC}"
    else
        printf "${GREEN} return OK ${NC}"
    fi
    echo
    echo -e "\n-------------------------------------\n" 
done
