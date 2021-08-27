#include "Print_Output.h"

Print_Output::Print_Output()
{

}

string Print_Output::print_line(vector<Term> container)
{
    string output_line;

    for (int i=0; i<container.size(); ++i) {
        if (container[i].isOperator == true) {
            output_line += container[i].awperator;
            // continue;
        }
        else if (container[i].isBrace == true) {
            output_line += container[i].brace;
        }
        else if (container[i].isEqualSign == true) {
            output_line += container[i].awperator;
        }
        else if (container[i].isConstant == true) {
            if (container[i].isFraction == true) {
                output_line += to_string(container[i].co_efficient_fraction[0]);
                output_line += "/";
                output_line += to_string(container[i].co_efficient_fraction[1]);
                output_line += " ";
            }
            else
                output_line += to_string(container[i].co_efficient);
        }
        else if (container[i].hasHardVal == true) {
                output_line += to_string(container[i].hard_value);
        }
        else {
            if (container[i].co_efficient > 1)
                output_line += to_string(container[i].co_efficient);
            else if (container[i].co_efficient < -1)
                output_line += to_string(container[i].co_efficient);
            else if (container[i].co_efficient == -1)
                output_line += "-";
            else if (container[i].co_efficient == 0)
                output_line += "0";
            else if (container[i].isFraction == true) {
                output_line += to_string(container[i].co_efficient_fraction[0]);
                output_line += "/";
                output_line += to_string(container[i].co_efficient_fraction[1]);
                output_line += " ";
            }

            for (int j=0; j<container[i].get_variable_count(); ++j) {
                output_line += container[i].variable_and_exponent[j].first;

                if (container[i].variable_and_exponent[j].second != 1) {
                    output_line += "^";
                    output_line += to_string(container[i].variable_and_exponent[j].second);
                }
            }
        }

        output_line += " ";
    }

    return output_line;
}

void Print_Output::take_input_from_ui(string input)
{
    this->inital_input_str = input;
    parser.take_input(inital_input_str);

    for (size_t i=0; i<parser.terms.size(); ++i)
        this->initial_input_line.push_back(parser.terms[i]);
}

void Print_Output::clear_all()
{
    inital_input_str.clear();
    initial_input_line.clear();

    parser.clear_all();
    process_linear_expression.clear_all();
    process_quadratic_expression.clear_all();
}

vector<Term> Print_Output::return_graph_expression()
{
    vector <Term> temp_line, returnVall;

//    int degree = algebraic_operation.highest_degree(initial_input_line);
//    if (degree == 2) {
//        temp_line = process_quadratic_expression.substitution_of_terms(initial_input_line);
//        returnVall = process_quadratic_expression.convert_to_standard_form(temp_line);
//    }
//    else if (degree == 1) {
//        temp_line = process_linear_expression.separate_variable_constant(initial_input_line);
//        returnVall = process_linear_expression.shorten_each_side(temp_line);
//        returnVall = process_quadratic_expression.convert_to_standard_form(returnVall);
//    }

    temp_line = process_quadratic_expression.substitution_of_terms(initial_input_line);
    returnVall = process_quadratic_expression.convert_to_standard_form(temp_line);

    return  returnVall;
}

string Print_Output::solve()
{
    string output = "";
    vector <vector<Term>> temp_process_container;

    temp_process_container.clear();

    int degree = algebraic_operation.highest_degree(initial_input_line);

    if (degree == 2){
        process_quadratic_expression.get_input(initial_input_line);
        temp_process_container = process_quadratic_expression.solve();
    }
    else if (degree == 1){
        process_linear_expression.get_input(initial_input_line);
        temp_process_container = process_linear_expression.solve();
    } else {
        return  output;
    }

    bool temp_flag = true;
    for (size_t i=0; i<temp_process_container.size(); ++i){
        if (temp_process_container[i][0].isEqualSign && temp_process_container[i][0].awperator[0] == '#') {
                        output += "\n";
                        if (temp_flag) { output += "If,\n";	temp_flag=false; }
                        else			 output += "Again,\n";
                        continue;
                    }
                    output += print_line(temp_process_container[i]);
                    output += '\n';
    }

    return  output;
}
