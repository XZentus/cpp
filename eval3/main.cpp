#include <iostream>
#include <memory>
//#include <random>
#include <vector>
#include <limits>
#include <algorithm>

#include <cmath>
#include <ctime>
//#include <cstdlib>

#include "expr.h"
#include "parameters.h"

using namespace std;

typedef double(*function)(const double &);

void make_points(function f, vector<double> & v) {
    v.clear();
    v.reserve(FITNESS_POINTS);
    
    for(int x = 0; x < FITNESS_POINTS; x += 1)
        v.emplace_back(f(FITNESS_MIN + FITNESS_STEP * double(x)));
}

void train(vector<Expr> & population, const vector<double> & points, const size_t & generations) {
    const size_t pop_size = population.size();
    vector<pair<Expr, double>> db;
    db.reserve(population.size());

    for(size_t i = 0; i < pop_size; i += 1) {
        auto & expr = population[i];
        double fit = expr.calc_fitness(points);

        db.emplace_back(move(expr), fit);
    }
    population.clear();

    for(size_t i = 0; i < generations; i += 1) {
        if(i % 100 == 0)
            cout << "Generation " << i << "..." << endl;

        //mutate, add mutated
        const auto current_len = db.size();
        
        for(size_t i = 0; i < current_len; i += 1) {
            Expr new_expr(db[i].first);
            if(!new_expr.mutate(DEPTH))
                continue;
            double fit = new_expr.calc_fitness(points);
            if(fit < db[i].second) {
                if(dis() < CHANCE_DUPLICATE)
                    db.emplace_back(move(new_expr), fit);
                else {
                    db[i].first = new_expr;
                    db[i].second = fit;
                }
            }
        }
        //cout << "\tMutate done" << endl;

        //sort
        sort(db.begin(), db.end(), [](const auto & a, const auto & b){ return a.second < b.second; });
        //cout << "\tSort done" << endl;

        //drop
        db.erase(db.begin() + INDIVIDUALS_SURVIVE, db.end());
        //cout << "\tDrop done" << endl;

        //add new
        for(size_t i = INDIVIDUALS_SURVIVE; i < POPULATION_SIZE; i += 1) {
            auto new_expr = Expr(DEPTH);
            double fit = new_expr.calc_fitness(points);
            db.emplace_back(move(new_expr), fit);
        }
        //cout << "\tNew creatures done" << endl;
    }

    population.clear();
    for(size_t i = 0; i < POPULATION_SIZE; i += 1) {
        auto e = db[i].first;
        //e.simplify();
        population.emplace_back(move(e));
    }
}

double target_fun(const double & x) {
    return cos(2.16327*x) + x*0.3423 - 3.0;
}

int main() {
    srand(time(0));
    vector<Expr> population;
    population.reserve(POPULATION_SIZE);
    
    for(size_t i = 0; i < POPULATION_SIZE; i += 1)
        population.emplace_back(10);
    
    vector<double> points;
    make_points(target_fun, points);

    cout << "Trainig begin..." << endl;
    train(population, points, 1500);
    cout << "Trainig done" << endl;

    for(size_t i = 0; i < 10; i += 1) {
        cout << population[i] << "\nFitness: " << population[i].calc_fitness(points) << endl;
        population[i].simplify();
        cout << population[i] << "\nFitness: " << population[i].calc_fitness(points) << "\n----------------------------------------\n" << endl;
    }
    
    return 0;
}
