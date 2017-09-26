#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;



int get_neighbours(vector<vector<int>> grid, vector<int> dims, int y, int x) {
	int count = 0;
	auto index = [&grid,&dims](int y1, int x1) {
		int n_y = (y1%dims[1]+dims[1])%dims[1];
		int n_x = (x1%dims[0]+dims[0])%dims[0];
		return grid[n_y][n_x];
	};
	if (index((y+1),(x-1)) == 1) {
		count+=1;
	}
	if (index((y+1),x) == 1) {
		count+=1;
	}
	if (index((y+1),(x+1)) == 1) {
		count+=1;
	}
	if (index(y,(x-1)) == 1) {
		count+=1;
	}
	if (index(y,(x+1)) == 1) {
		count+=1;
	}
	if (index((y-1),(x-1)) == 1) {
		count+=1;
	}
	if (index((y-1),x) == 1) {
		count+=1;
	}
	if (index((y-1),(x+1)) == 1) {
		count+=1;
	}
	return count;
	cout << endl;
}

vector<vector<int>> iterate(vector<vector<int>> grid, vector<int> dims) {
	vector<vector<int>> new_grid = grid;
	for (int i=0;i<dims[1];++i) {
		for (int j=0;j<dims[0];++j) {
			int n_neighbours = get_neighbours(grid,dims,i,j);
			if (n_neighbours == 3 && grid[i][j] == 0) {
				new_grid[i][j] = 1;
			}
			else if ((n_neighbours < 2 || n_neighbours > 3) && grid[i][j] == 1) {
				new_grid[i][j] = 0;
			}
		}
	}
	return new_grid;
}

vector<int> get_dims() {
	vector<int> v_dims;
	int this_dim;
	FILE *fp = popen("tput cols;tput lines","r");
	char buf[1024];
	while (fgets(buf,1024, fp)) {
		this_dim = atoi(buf);
		v_dims.push_back(this_dim);
	}
	fclose(fp);
	return v_dims;
}

vector<vector<int>> create_grid(vector<int> dims, int freq) {
	vector<vector<int>> grid;
	vector<int> this_row;
	int num;
	
	for (int i=0;i<dims[0];++i) {
		this_row.push_back(0);
	}
	for (int i=0;i<dims[1];++i) {
		grid.push_back(this_row);
	}
	
	for (int i=0;i<dims[1];++i) {
		for (int j=0;j<dims[0];++j) {
			num = rand()%100;
			if (num<freq) {
				grid[i][j] = 1;
			}
			else {
				grid[i][j] = 0;
			}
		}
	}	

	return grid;
}

void save_gen() {

}

void output_gen(vector<vector<int>> grid, vector<int> dims) {
	for (int i=0;i<dims[1];++i) {
		for (int j=0;j<dims[0];++j) {
			switch(grid[i][j]) {
				case 0: cout << " "; break;
				case 1: cout << "O"; break;
			}
			//cout << grid[i][j];
		}
		cout << endl;
	}
}

int main() {
	system("clear");
	srand(time(NULL));
	int freq = 50;
	vector<int> dims = get_dims();
	vector<vector<int>> this_gen,next_gen;
	this_gen = create_grid(dims,freq);
	
	while (true) {
		//system("clear");
		output_gen(this_gen,dims);
		next_gen = iterate(this_gen, dims);
		this_gen = next_gen;
		//sleep(0.1);
	}

	return 0;
}
