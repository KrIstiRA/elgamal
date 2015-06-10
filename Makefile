all:
	g++ gen_elgamal_keys.cpp largeClass/largeClass.cpp largeClass/largeNum.cpp -o gen_elgamal_keys
	g++ elgamal.cpp largeClass/largeClass.cpp largeClass/largeNum.cpp -o elgamal
