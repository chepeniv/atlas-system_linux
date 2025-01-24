mkdir empty.ignore another.ignore
chmod a-r empty.ignore another.ignore

echo ======== HLS.EXEC ========

./hls.exec
echo ----------------
./hls.exec .
echo ----------------
./hls.exec prototypes/
echo ----------------
./hls.exec ../getline prototypes
echo ----------------
./hls.exec makefile
echo ----------------
./hls.exec makefile README.md
echo ----------------
./hls.exec makefile prototypes
echo ----------------
./hls.exec empty.ignore
echo ----------------
./hls.exec empty.ignore makefile
echo ----------------
./hls.exec empty.ignore prototypes
echo ----------------
./hls.exec doesnotexist
echo ----------------
./hls.exec doesnotexist empty.ignore
echo ----------------
./hls.exec doesnotexist prototypes
echo ----------------
./hls.exec doesnotexist makefile
echo ----------------
./hls.exec doesnotexist prototypes makefile empty.ignore

# echo ======== LS ========

# ls
# echo ----------------
ls .
echo ----------------
ls prototypes/
echo ----------------
# ls ../getline prototypes
# echo ----------------
# ls makefile
# echo ----------------
# ls makefile README.md
# echo ----------------
# ls makefile prototypes
# echo ----------------
# ls empty.ignore
# echo ----------------
# ls empty.ignore makefile
# echo ----------------
# ls empty.ignore prototypes
# echo ----------------
# ls doesnotexist
# echo ----------------
# ls doesnotexist empty.ignore
# echo ----------------
# ls doesnotexist prototypes
# echo ----------------
# ls doesnotexist makefile
# echo ----------------
# ls doesnotexist prototypes makefile empty.ignore

rmdir empty.ignore another.ignore
