#include <iostream>
#include <fstream>
#include <ios>

#include <vector>
#include <set>

using namespace std;

struct Pos {
    size_t row;
    size_t col;
    
    Pos ( const size_t & r = 0, const size_t & c = 0 ):
        row(r), col(c) { } ;
};

typedef vector<vector<int>> matrix;

matrix test =
    {   { 131, 673, 234, 103,  18 },
        { 201,  96, 342, 965, 150 },
        { 630, 803, 746, 422, 111 },
        { 537, 699, 497, 121, 956 },
        { 805, 732, 524,  37, 331 } };

matrix output, input;

template < typename T, typename M >
void init_out_vector( const size_t & rows, const size_t & cols, const T & init_value, M & vec ) {
    vec.reserve(rows);
    for ( size_t row = 0; row < rows ; row += 1 )
        vec.emplace_back( cols, init_value );
}

template < typename M >
void print_matrix( const M & m ) {
    for ( const auto & row: m ) {
        for ( const auto & e: row )
            cout << e << ' ';
        cout << '\n';
    }
}

bool operator< ( const Pos & p1, const Pos & p2 ) {
    if ( p1.row == p2.row )
        return p1.col < p2.col;
    return p1.row < p2.row;
}

void fill_out_vector( const matrix & in = input, matrix & out = output ) {
    set < Pos > points;
    points.emplace( 0, 0 );
    out[0][0] = in[0][0];
    const size_t rows = out.size(), cols = out[0].size();
    
    while ( !points.empty() ) {
        
        const auto begin = points.begin();

        const size_t row = begin->row, col = begin->col;

        points.erase(begin);
        
        const auto & from = out[row][col];
        
        if ( row > 0 ) {
            int tmp = in[row - 1][col] + from;
            if ( tmp < out[row - 1][col] ) {
                out[row - 1][col] = tmp;
                points.emplace(row - 1, col);
            }
        }
        if ( col > 0 ) {
            int tmp = in[row][col - 1] + from;
            if ( tmp < out[row][col - 1] ) {
                out[row][col - 1] = tmp;
                points.emplace(row, col - 1);
            }
        }
        
        if ( row < rows - 1 ) {
            int tmp = in[row + 1][col] + from;
            if ( tmp < out[row + 1][col] ) {
                out[row + 1][col] = tmp;
                points.emplace(row + 1, col);
            }
        }
        if ( col < cols - 1 ) {
            int tmp = in[row][col + 1] + from;
            if ( tmp < out[row][col + 1] ) {
                out[row][col + 1] = tmp;
                points.emplace(row, col + 1);
            }
        }
    }
}

int main () {
    ios::sync_with_stdio(false);
    
    { // file reading section
        ifstream in;
        in.open("p083_matrix.txt");
    
        if ( !in.is_open() ) {
            cerr << "failed to open ..." << endl;
            return 1;
        }
        
        input.emplace_back();
        while ( !in.eof() ) {
            int num;
            char c;
            in >> num;
            input.back().emplace_back(num);
            if ( in.peek() == '\n' ) {
                input.emplace_back();
            }
            else
                in >> c;
        }
        
        in.close();
    }
    input.pop_back();
    
    init_out_vector( input.size(), input[0].size(), 0x0fffffff, output );


    fill_out_vector();
    
    cout << output.back().back() << '\n';
    
    return 0;
}