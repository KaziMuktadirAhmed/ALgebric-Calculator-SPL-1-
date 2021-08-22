#include "Process_Linear_Expression.h"

Process_Linear_Expression::Process_Linear_Expression()
{

}

void Process_Linear_Expression::get_input(string str_input)
{
    initial_input.clear();
    parser.take_input(str_input);

    for (size_t i=0; i<parser.terms.size(); ++i)
        initial_input.push_back(parser.terms[i]);

    algebraic_opeartion.normalize_terms(initial_input);
}

void Process_Linear_Expression::get_input(vector<Term> vec_input)
{
    initial_input.clear();
    for (size_t i=0; i<vec_input.size(); ++i)
        initial_input.push_back(vec_input[i]);

    algebraic_opeartion.normalize_terms(initial_input);
}

Term Process_Linear_Expression::reverse_operator(Term input)
{
    Term result;

    if (input.isOperator == true) {

        if (input.awperator.compare("+") == 0) {
            result.isOperator = true;
            result.awperator = "-";
        }
        else if (input.awperator.compare("-") == 0) {
            result.isOperator = true;
            result.awperator = "+";
        }
        else if (input.awperator.compare("*") == 0) {
            result.isOperator = true;
            result.awperator = "/";
        }
        else if (input.awperator.compare("/") == 0) {
            result.isOperator = true;
            result.awperator = "*";
        }
    }

    return result;
}

vector<Term> Process_Linear_Expression::separate_variable_constant(vector<Term> input_line)
{
            int equal_index = 0;
            vector <Term> result, LHS, RHS;

            Term plus_sign, equal_sign, zero;

            plus_sign.isOperator = true;
            plus_sign.awperator = "+";

            equal_sign.isEqualSign = true;
            equal_sign.awperator = "=";

            zero.isConstant = true;
            zero.co_efficient = 0;

            for (int i=0; input_line[i].isEqualSign != true; ++i) {
                // keeping a record of last variable term //
                equal_index = i;

                if (input_line[i].isOperator == false && input_line[i].isBrace == false) {
                    // secondary if filter //
                    if (input_line[i].isConstant == false) {
                        if (i == 0) {
                            LHS.push_back(plus_sign);
                            LHS.push_back(input_line[i]);
                        }
                        else {
                            if (input_line[i-1].isOperator == true)
                                LHS.push_back(input_line[i-1]);

                            LHS.push_back(input_line[i]);
                        }
                    }
                    else {
                        if (i == 0) {
                            RHS.push_back(reverse_operator(plus_sign));
                            RHS.push_back(input_line[i]);
                        }
                        else {
                            if (input_line[i-1].isOperator == true)
                                RHS.push_back(reverse_operator(input_line[i-1]));

                            RHS.push_back(input_line[i]);
                        }
                    }
                }

            }	equal_index++;

            for (int i = equal_index + 1; i<input_line.size(); ++i) {

                if (input_line[i].isOperator == false && input_line[i].isBrace == false) {
                    // secondary if filter //
                    if (input_line[i].isConstant == false) {
                        if (i == equal_index + 1) {
                            LHS.push_back(reverse_operator(plus_sign));
                            LHS.push_back(input_line[i]);
                        }
                        else {
                            if (input_line[i-1].isOperator == true)
                                LHS.push_back(reverse_operator(input_line[i-1]));

                            LHS.push_back(input_line[i]);
                        }
                    }
                    else {
                        if (i == equal_index + 1) {
                            RHS.push_back(plus_sign);
                            RHS.push_back(input_line[i]);
                        }
                        else {
                            if (input_line[i-1].isOperator == true)
                                RHS.push_back(input_line[i-1]);

                            RHS.push_back(input_line[i]);
                        }
                    }
                }
            }

            if (LHS.size() == 0)
                LHS.push_back(zero);

            if (RHS.size() == 0)
                RHS.push_back(zero);

            if (LHS[0].isOperator == true && LHS[0].awperator.compare("+") == 0)
                LHS.erase(LHS.begin());

            if (RHS[0].isOperator == true && RHS[0].awperator.compare("+") == 0)
                RHS.erase(RHS.begin());


            for (size_t i=0; i<LHS.size(); ++i)
                result.push_back(LHS[i]);

            result.push_back(equal_sign);

            for (size_t i=0; i<RHS.size(); ++i)
                result.push_back(RHS[i]);

            return result;
}

vector<Term> Process_Linear_Expression::shorten_each_side(vector<Term> input_line)
{
    int equal_sign_index = 0;
    vector <Term> result, LHS, RHS;
    Term temp, op_t1, op_t2, eql_sign, zero;

    eql_sign.isEqualSign = true;
    eql_sign.awperator = "=";

    zero.isConstant = true;
    zero.co_efficient = 0;

    op_t1.isOperator = true;
    op_t2.isOperator = true;

    for (int i=0; input_line[i].isEqualSign == false; ++i) {
        if (input_line[i].isBrace == false && input_line[i].isOperator == false && input_line[i].isConstant == false) {
            if (temp.isEmpty()) {
                temp = input_line[i];

                if (i == 0)
                    op_t1.awperator = "+";
                else
                    if (input_line[i-1].isOperator == true) {
                        op_t1.awperator = input_line[i-1].awperator;
                    }
            }
            else {
                if (input_line[i-1].isOperator == true) {
                    op_t2.awperator = input_line[i-1].awperator;
                }

                if (op_t1.awperator.compare("-") == 0 && temp.co_efficient > 0) {
                    temp.co_efficient *= -1;
                }

                if (op_t2.awperator.compare("+") == 0) {
                    temp = algebraic_opeartion.add_term(temp, input_line[i]);
                }
                else if (op_t2.awperator.compare("-") == 0)
                    temp = algebraic_opeartion.sub_term(temp, input_line[i]);

                if (temp.co_efficient < 0) {
                    op_t1.awperator = "-";
                    temp.co_efficient *= -1;
                }
                else
                    op_t1.awperator = "+";
            }
        }

        ++equal_sign_index;
    }

    if (op_t1.awperator.compare("-") == 0)
        LHS.push_back(op_t1);

    if (temp.co_efficient == 0)
        temp = zero;

    LHS.push_back(temp);

    temp.reset();
    op_t1.reset();
    op_t2.reset();

    op_t1.isOperator = true;
    op_t2.isOperator = true;

    for (int i=equal_sign_index+1; i<input_line.size(); ++i) {
        if (input_line[i].isConstant == true) {
            if (temp.isEmpty()) {
                temp = input_line[i];

                if (i == 0)
                    op_t1.awperator = "+";
                else
                    if (input_line[i-1].isOperator == true) {
                        op_t1.awperator = input_line[i-1].awperator;
                    }
            }
            else {
                if (input_line[i-1].isOperator == true) {
                    op_t2.awperator = input_line[i-1].awperator;
                }

                if (op_t1.awperator.compare("-") == 0 && temp.co_efficient > 0) {
                    temp.co_efficient *= -1;
                }

                if (op_t2.awperator.compare("+") == 0) {
                    temp = algebraic_opeartion.add_term(temp, input_line[i]);
                }
                else if (op_t2.awperator.compare("-") == 0)
                    temp = algebraic_opeartion.sub_term(temp, input_line[i]);

                if (temp.co_efficient < 0) {
                    op_t1.awperator = "-";
                    temp.co_efficient *= -1;
                }
                else
                    op_t1.awperator = "+";
            }
        }
    }

    if (op_t1.awperator.compare("-") == 0) {
        RHS.push_back(op_t1);
    }

    if (temp.co_efficient == 0)
        temp = zero;

    RHS.push_back(temp);

    for (size_t i=0; i<LHS.size(); ++i)
        result.push_back(LHS[i]);

    result.push_back(eql_sign);

    for (size_t i=0; i<RHS.size(); ++i)
        result.push_back(RHS[i]);

    return result;
}

vector<vector<Term> > Process_Linear_Expression::solve()
{
    vector <vector <Term>> whole_process;
    vector <Term> last_processable_line, temp_line;

    Term div_sign, mul_sign, constant;

    if (initial_input.size() == 0) {
        cout << "No initial input line given\n";
        return whole_process;
    }

    div_sign.isOperator = true;
    div_sign.awperator = "/";

    mul_sign.isOperator = true;
    mul_sign.awperator = "*";

    whole_process.push_back(initial_input);
    whole_process.push_back(separate_variable_constant(initial_input));

    last_processable_line = shorten_each_side(whole_process[1]);
    whole_process.push_back(shorten_each_side(last_processable_line));

    int flag = -99999, temp_index = 0;
    for (int i=0; i<last_processable_line.size(); ++i) {
        if (last_processable_line[i].isOperator && last_processable_line[i].awperator.compare("-") == 0)
            flag = i;
        else {
            temp_line.push_back(last_processable_line[i]);

            if (i == flag + 1 && last_processable_line[i].isEqualSign == false) {
                temp_line[temp_index].co_efficient *= -1;
                flag = -1;
            }

            ++temp_index;
        }
    }

    // string out = print_line(temp_line);
    // cout << out;

    constant.isConstant = true;
    constant.co_efficient = temp_line[0].co_efficient;

    temp_line[0] = algebraic_opeartion.div_term(temp_line[0], constant);
    temp_line[2] = algebraic_opeartion.div_term(temp_line[2], constant);

    // out = print_line(temp_line);
    // cout << out;

    whole_process.push_back(temp_line);

    return whole_process;
}

string Process_Linear_Expression::print_line(vector<Term> container)
{
    string output_line;

    for (size_t i=0; i<container.size(); ++i) {
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
