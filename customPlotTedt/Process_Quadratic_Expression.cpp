#include "Process_quadratic_expression.h"

Process_Quadratic_Equation::Process_Quadratic_Equation()
{

}

void Process_Quadratic_Equation::get_input(string str_input)
{
    initial_equation.clear();
    parser.take_input(str_input);

    for (size_t i=0; i<parser.terms.size(); ++i)
        initial_equation.push_back(parser.terms[i]);

    algebraic_operation.normalize_terms(initial_equation);
}

void Process_Quadratic_Equation::get_input(vector<Term> vec_input)
{
    initial_equation.clear();
    for (size_t i=0; i<vec_input.size(); ++i)
        initial_equation.push_back(vec_input[i]);

    algebraic_operation.normalize_terms(initial_equation);
}

int Process_Quadratic_Equation::find_highest_exponent(vector<Term> input)
{
    int highest_exponent = 0;

    algebraic_operation.normalize_terms(input);

    for (size_t i=0; i<input.size(); ++i) {
        if (input[i].isBrace || input[i].isEqualSign || input[i].isOperator || input[i].isEmpty())
            continue;

        for (size_t j=0; j<input[i].get_variable_count(); ++j) {
            if (input[i].variable_and_exponent[j].second > highest_exponent)
                highest_exponent = input[i].variable_and_exponent[j].second;
        }
    }

    return highest_exponent;
}

bool Process_Quadratic_Equation::isQuadraticEqation()
{
    bool returnValue = false;

    if(find_highest_exponent(initial_equation) == 2)
        returnValue = true;

    return returnValue;
}

bool Process_Quadratic_Equation::isQuadraticEqation(vector<Term> input)
{
    bool returnValue = false;

    if(find_highest_exponent(input) == 2)
        returnValue = true;

    return returnValue;
}

Term Process_Quadratic_Equation::reverse_operator(Term input)
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

vector<Term> Process_Quadratic_Equation::substitution_of_terms(vector<Term> input)
{
    vector <Term> final_expression;
    int equal_index = 0;
    bool foundEqualSign = false;
    Term plus_sign, minus_sign, equal_sign, zero;

    plus_sign.isOperator = true;
    plus_sign.awperator = "+";

    minus_sign.isOperator = true;
    minus_sign.awperator = "-";

    equal_sign.isEqualSign = true;
    equal_sign.awperator = "=";

    zero.isConstant = true;
    zero.co_efficient = 0;

    for (equal_index=0; input[equal_index].isEqualSign == false; ++equal_index)
        if (input[equal_index].co_efficient != 0)
            final_expression.push_back(input[equal_index]);

    bool passed_operator = false;

    for (int i = equal_index + 1; i<input.size(); ++i) {
        if (input[i].isOperator == true) {
            if (input[i].awperator[0] == '+')
                final_expression.push_back(minus_sign);
            else if (input[i].awperator[0] == '-')
                final_expression.push_back(plus_sign);

            passed_operator = true;
        }
        else if (input[i].co_efficient != 0) {
            if (passed_operator == true)
                final_expression.push_back(input[i]);
            else {
                final_expression.push_back(minus_sign);
                final_expression.push_back(input[i]);
            }
        }
    }

    final_expression.push_back(equal_sign);
    final_expression.push_back(zero);

    return final_expression;
}

vector<Term> Process_Quadratic_Equation::convert_to_standard_form(vector<Term> input)
{
    vector <Term> final_expression;

    int highest_power = find_highest_exponent(input);

    bool flag = false;
    Term demo, demo_op, plus_sign, minus_sign, equal_sign, zero;

    plus_sign.isOperator = true;
    plus_sign.awperator = "+";

    minus_sign.isOperator = true;
    minus_sign.awperator = "-";

    equal_sign.isEqualSign = true;
    equal_sign.awperator = "=";

    zero.isConstant = true;
    zero.co_efficient = 0;

    while (highest_power > -1)
    {
        if (highest_power > 0)
        {
            for (int i=0; input[i].isEqualSign == false; ++i) {
                if(!input[i].isConstant && !input[i].isBrace && !input[i].isOperator && input[i].variable_and_exponent[0].second == highest_power) {
                    if (!flag) {
                        demo = input[i];
                        if (i == 0)	demo_op = plus_sign;
                        else demo_op = input[i-1];
                        flag = true;
                    }
                    else {
                        if (demo_op.awperator[0] == input[i-1].awperator[0]) {
                            demo = algebraic_operation.add_term(demo, input[i]);
                            demo_op = input[i-1];
                        }
                        else {
                            if (demo.co_efficient > input[i].co_efficient)
                                demo = algebraic_operation.sub_term(demo, input[i]);
                            else {
                                demo = algebraic_operation.sub_term(input[i], demo);
                                demo_op = input[i-1];
                            }
                        }
                    }
                }
            }
        }

        else {
            for (int i=0; i<input.size(); ++i) {
                if (input[i].isConstant == true) {
                    if (!flag) {
                        demo = input[i];
                        if (i == 0) demo_op = plus_sign;
                        else demo_op = input[i-1];
                        flag = true;
                    }
                    else {
                        if (demo_op.awperator[0] == input[i-1].awperator[0]) {
                            demo = algebraic_operation.add_term(demo, input[i]);
                            demo_op = input[i-1];
                        }
                        else {
                            if (demo.co_efficient > input[i].co_efficient)
                                demo = algebraic_operation.sub_term(demo, input[i]);
                            else {
                                demo = algebraic_operation.sub_term(input[i], demo);
                                demo_op = input[i-1];
                            }
                        }
                    }
                }
            }

        }

        if (!demo.isEmpty() && !demo_op.isEmpty() && demo.co_efficient != 0){
            final_expression.push_back (demo_op);
            final_expression.push_back (demo);
        }

        demo.reset();
        demo_op.reset();
        flag = false;

        --highest_power;
    }

    if (final_expression[0].isOperator == true && final_expression[0].awperator[0] == '+')
        final_expression.erase(final_expression.begin() + 0);

    final_expression.push_back (equal_sign);
    final_expression.push_back (zero);

    return final_expression;
}

int Process_Quadratic_Equation::cheak_for_integer_root(vector<Term> input)
{
    int has_integer_root = -1;

    int a = 0, b = 0, c = 0;

    for (int i=0; input[i].isEqualSign == false; ++i) {
        if (!input[i].isOperator && !input[i].isBrace) {
            if (input[i].isConstant == true){
                c = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	c *= -1;
            }
            else if (input[i].variable_and_exponent[0].second == 1) {
                b = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	b *= -1;
            }
            else if (input[i].variable_and_exponent[0].second == 2) {
                a = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	a *= -1;
            }
        }
    }

    int discriminant = b*b - 4*a*c, temp;

    if (discriminant < 0.0)
        return has_integer_root;
    else
        has_integer_root = 0;

    double cheak = 0.0;

    if (discriminant >= 0) {
        temp = sqrt(discriminant);
        cheak = sqrt(discriminant);

        cheak -= (double)temp;

        if (cheak == 0.0)
            has_integer_root = 1;
    }

    return has_integer_root;
}

pair<int, int> Process_Quadratic_Equation::find_int_root(vector<Term> input)
{
    if (cheak_for_integer_root(input) == false)
        return make_pair(INT_MIN, INT_MIN);

    int a = 0, b = 0, c = 0;
    pair <int, int> root;

    for (int i=0; input[i].isEqualSign == false; ++i) {
        if (!input[i].isOperator && !input[i].isBrace) {
            if (input[i].isConstant == true){
                c = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	c *= -1;
            }
            else if (input[i].variable_and_exponent[0].second == 1) {
                b = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	b *= -1;
            }
            else if (input[i].variable_and_exponent[0].second == 2) {
                a = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	a *= -1;
            }
        }
    }

    double t1 = (-b + sqrt(b*b - 4*a*c))/(2*a), t2 = (-b - sqrt(b*b - 4*a*c))/(2*a);

    int temp = (-b + sqrt(b*b - 4*a*c))/(2*a);
    if ((t1 - (double)temp) > 0.0)
        root.first = t1;
    else
        root.first = t2;

    temp = (-b - sqrt(b*b - 4*a*c))/(2*a);
    root.second = temp;

    return root;
}

pair<double, double> Process_Quadratic_Equation::find_real_root(vector<Term> input)
{
    if (cheak_for_integer_root(input) < 0)
        return make_pair(INT_MIN, INT_MIN);

    int a = 0, b = 0, c = 0;
    pair <double, double> root;

    for (int i=0; input[i].isEqualSign == false; ++i) {
        if (!input[i].isOperator && !input[i].isBrace) {
            if (input[i].isConstant == true){
                c = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	c *= -1;
            }
            else if (input[i].variable_and_exponent[0].second == 1) {
                b = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	b *= -1;
            }
            else if (input[i].variable_and_exponent[0].second == 2) {
                a = input[i].co_efficient;
                if (i > 0 && input[i-1].awperator[0] == '-')	a *= -1;
            }
        }
    }

    double temp = (-b + sqrt(b*b - 4*a*c))/(2*a);
    root.first = temp;

    temp = (-b - sqrt(b*b - 4*a*c))/(2*a);
    root.second = temp;

    return root;
}

vector<vector<Term> > Process_Quadratic_Equation::remainder_theorum(vector<Term> input)
{
    vector <vector <Term>> returnVal;
    pair <int, int> root = find_int_root (input);

    // creating initial factor
    vector <Term> factor, allFacotors;
    Term demo;

    demo.reset();
    demo.co_efficient = 1;
    {
        string str;
        if (!input[0].isOperator)	str = input[0].variable_and_exponent[0].first;
        else if (!input[1].isOperator)	str = input[1].variable_and_exponent[0].first;
        demo.variable_and_exponent.push_back(make_pair(str, 1));
    }

    factor.push_back(demo);
    demo.reset();

    demo.isOperator = true;

    if (root.first > 0)
        demo.awperator = "-";
    else if (root.first < 0)
        demo.awperator = "+";

    if (root.first != 0)
        factor.push_back(demo);

    demo.reset();

    if (root.first != 0) {
        demo.isConstant = true;
        demo.co_efficient = abs(root.first);
        demo.co_efficient_fraction[0] = 1; demo.co_efficient_fraction[1] = 1;
        factor.push_back(demo);
        demo.reset();
    }
    // initial factor x +/- a created

    vector <Term> temp_line;
    returnVal.push_back(temp_line);
    returnVal.push_back(temp_line);

    Term op_brace, cls_brace, equal_sign, zero;
    Term demo_op;

    op_brace.isBrace = true;
    op_brace.brace = "(";

    cls_brace.isBrace = true;
    cls_brace.brace = ")";

    equal_sign.isEqualSign = true;
    equal_sign.awperator = "=";

    zero.isConstant = true;
    zero.co_efficient = 0;

    int j = -1;
    demo.reset();
    demo_op.reset();

    bool will_loop_to_next = true;
    for (int i=0; will_loop_to_next && input[i].isEqualSign == false; ++i)
    {
        if (!input[i].isOperator && !input[i].isBrace) {
            if (i == 0 || i == 1){
                if (i > 0)
                    demo_op = input[i-1];
                demo = input[i];
            }
            else {
                int diff, n1, n2;

                if (algebraic_operation.is_operable(demo, input[i]) != 1 && algebraic_operation.is_operable(demo, input[i]) != 2)
                    n1 = 0;
                else if (input[i-1].isOperator && input[i-1].awperator[0] == '-')
                    n1 = -1 * input[i].co_efficient;
                else n1 = abs(input[i].co_efficient);

                if (demo_op.isOperator && demo_op.awperator[0] == '-')
                    n2 = -1 * demo.co_efficient;
                else n2 = abs(demo.co_efficient);

                diff = n1 - n2;

                if (diff > 0) {
                    demo_op.isOperator = true;
                    demo_op.awperator = "+";
                } else if (diff < 0) {
                    demo_op.isOperator = true;
                    demo_op.awperator = "-";
                } else break;
                demo.co_efficient = abs(diff);
            }

            // first entry
            if (demo_op.isOperator) {
                returnVal[0].push_back(demo_op);	++j;
                returnVal[1].push_back(demo_op);
            }

            returnVal[0].push_back(demo);	++j;

            if (demo.variable_and_exponent[0].second > 1)
                demo.variable_and_exponent[0].second -= 1;
            else if (demo.variable_and_exponent[0].second == 1) {
                demo.isConstant = true;
                demo.variable_and_exponent.clear();
                will_loop_to_next = false;
            }
            returnVal[1].push_back(demo);

            returnVal[1].push_back(op_brace);
            for(int k=0; k<factor.size(); ++k)
                returnVal[1].push_back(factor[k]);
            returnVal[1].push_back(cls_brace);

            if (demo_op.isOperator) 	demo_op = algebraic_operation.multiply_operator(demo_op, factor[1]);
            else 	demo_op = factor[1];
            returnVal[0].push_back(demo_op); 	++j;

            demo = algebraic_operation.mul_term(demo, factor[2]);
            returnVal[0].push_back(demo);	++j;
        }
    }

    returnVal[0].push_back(equal_sign);
    returnVal[0].push_back(zero);

    returnVal[1].push_back(equal_sign);
    returnVal[1].push_back(zero);

    // final factorized line
    temp_line.push_back(op_brace);
    bool shouuld_take = true;
    for (int i=0; returnVal[1][i].isEqualSign == false; ++i) {
        if (returnVal[1][i].isBrace && returnVal[1][i].brace[0] == '(')
            shouuld_take = false;

        if (shouuld_take) {
            temp_line.push_back(returnVal[1][i]);
        } else {
            if (returnVal[1][i].isBrace && returnVal[1][i].brace[0] == ')')
                shouuld_take = true;
        }
    } temp_line.push_back(cls_brace);

    temp_line.push_back(op_brace);
    for (int i=0; i<factor.size(); ++i)
        temp_line.push_back(factor[i]);
    temp_line.push_back(cls_brace);

    temp_line.push_back(equal_sign);
    temp_line.push_back(zero);
    returnVal.push_back(temp_line);

    return returnVal;
}

void Process_Quadratic_Equation::extract_factor_equation(vector<Term> input)
{
    vector <Term> temp_line;
    Term equal_sign, zero;

    equal_sign.isEqualSign = true;
    equal_sign.awperator = "=";

    zero.isConstant = true;
    zero.co_efficient = 0;

    bool should_take = false;
    for (int i=0; input[i].isEqualSign == false; ++i) {
        if (input[i].isBrace && input[i].brace[0] == '(') {
            should_take = true;
            continue;
        }

        if (should_take) {
            if (input[i].isBrace && input[i].brace[0] == ')') {
                should_take = false;

                temp_line.push_back(equal_sign);
                temp_line.push_back(zero);

                factor_eqations.push_back(temp_line);
                temp_line.clear();
            }
            else
                temp_line.push_back(input[i]);
        }
    }
}

vector <vector<Term>> Process_Quadratic_Equation::solve()
{
    vector <vector <Term>> whole_process, temp_process_container;
    vector <Term> last_processed_line, temp_line, end_line;

    last_processed_line.assign(initial_equation.begin(), initial_equation.end());
    whole_process.push_back(last_processed_line);

    temp_line.clear();
    temp_line = substitution_of_terms(last_processed_line);

    if (!algebraic_operation.compare_line(temp_line, last_processed_line)){
        last_processed_line.clear();
        last_processed_line = temp_line;
        whole_process.push_back(temp_line);
    }

    temp_line.clear();
    temp_line = convert_to_standard_form(last_processed_line);

    if (!algebraic_operation.compare_line(temp_line, last_processed_line)){
        last_processed_line.clear();
        last_processed_line = temp_line;
        whole_process.push_back(temp_line);
    }

    if (isQuadraticEqation(last_processed_line) == false) {
        process_linear_expression.get_input(last_processed_line);

        temp_process_container.clear();
        temp_process_container = process_linear_expression.solve();

        whole_process.insert(whole_process.end(), temp_process_container.begin(), temp_process_container.end());

        return whole_process;
    }

    if (cheak_for_integer_root(last_processed_line) < 1)
    {
        if (cheak_for_integer_root(last_processed_line) == 0) {
            Term var_x, const_val, equal_sign;
            pair <double, double> real_root = find_real_root(last_processed_line);

            var_x.co_efficient = 1;
            for (int i=0; i<last_processed_line.size(); ++i)
                if (!last_processed_line[i].isBrace && !last_processed_line[i].isOperator && !last_processed_line[i].isEqualSign && !last_processed_line[i].isConstant) {
                    var_x.variable_and_exponent.push_back(make_pair(last_processed_line[i].variable_and_exponent[0].first, 1));
                    break;
            }

            equal_sign.isOperator = true;
            equal_sign.awperator = "=";

            const_val.hasHardVal = true;
            const_val.hard_value = real_root.first;

            temp_line.clear();
            temp_line.push_back(var_x);
            temp_line.push_back(equal_sign);
            temp_line.push_back(const_val);

            whole_process.push_back(temp_line);

            temp_line.clear();
            const_val.hard_value = real_root.second;

            temp_line.push_back(var_x);
            temp_line.push_back(equal_sign);
            temp_line.push_back(const_val);

            whole_process.push_back(temp_line);
        }

        return whole_process;
    }

    temp_process_container = remainder_theorum(last_processed_line);
    for (int i=0; i<temp_process_container.size();  ++i)
        whole_process.push_back(temp_process_container[i]);

    last_processed_line = whole_process[whole_process.size()-1];
    extract_factor_equation(last_processed_line);

    Term end_sign;
    end_sign.isEqualSign = true;
    end_sign.awperator = "#";
    end_line.push_back(end_sign);

    for (int i=0; i<factor_eqations.size(); ++i) {
        process_linear_expression.get_input(factor_eqations[i]);

        temp_process_container.clear();
        temp_process_container = process_linear_expression.solve();

        whole_process.push_back(end_line);
        whole_process.insert(whole_process.end(), temp_process_container.begin(), temp_process_container.end());
    }

    return whole_process;
}

void Process_Quadratic_Equation::clear_all()
{
    parser.clear_all();
    process_linear_expression.clear_all();

    initial_equation.clear();
    factor_eqations.clear();
}
