install:
	g++ -std=c++11 -Wno-sign-compare -Wno-enum-compare -I. rest-server.cpp -o rest-server -Wl,-R/app/lib -L. -lcpprest -lboost_system -lssl -lcrypto
	mv rest-server run.sh /app/bin/
	cp libcpprest.so.2.8 /app/lib/
