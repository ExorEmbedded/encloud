# Build from scratch and test making sure Qmake is called
#
# WARNING: cleans untracked files!!!

git clean -fdX . && \
qmake && \
make

if [ $? -ne 0 ]; then
    echo "Failure in build."
    exit 1
fi

exit 0
