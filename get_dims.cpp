//#include <cstdio>
#include <iostream>
//#include <memory>
//#include <stdexcept>
#include <string>
#include <array>
#include <string>

using namespace std;

int main () {
	FILE *fp = popen("tput cols;tput lines","r");
	char buf[1024];

	while (fgets(buf,1024, fp)) {
	cout << buf;
	}
	fclose(fp);
	string str(buf);
	return 0;
}
