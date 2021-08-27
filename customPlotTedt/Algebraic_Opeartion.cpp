#include "Algebraic_Opeartion.h"

Algebraic_Opeartion::Algebraic_Opeartion()
{

}

int Algebraic_Opeartion::is_operable(Term a, Term b)
{
    /*
        The funtion takes 2 term a and b as input. depending on the input the funtion
        retuns a integer value between -1 to 3. They represent

        -1 = inoperable condition (a or b contains brace/equalSign/operator)
        0  = can only perform multiplication or division (either a  or b is constant)
        1  = all operation can be performed (both a and b are constant)
        2  = all operation can be performed (both a and b has same variable and exponent list)
        3  = can only perform multiplication or division (a and b contains diffrent set of variable and exponents)
    */

            if(a.isBrace || b.isBrace)
                return -1;
            else if (a.isEqualSign || b.isEqualSign)
                return -1;
            else if (a.isOperator || b.isOperator)
                return -1;
            else if (a.isConstant && !(b.isConstant) )
                return 0;
            else if (!(a.isConstant) && b.isConstant)
                return 0;
            else if (a.isConstant && b.isConstant)
                return 1;
            else {
                bool flag = true;

                if (a.get_variable_count() != b.get_variable_count())
                    flag = false;
                else {
                    for (int i=0; i<a.get_variable_count(); ++i) {
                        if (a.variable_and_exponent[i].first.compare(b.variable_and_exponent[i].first) != 0)
                            flag = false;
                        else if(a.variable_and_exponent[i].second != b.variable_and_exponent[i].second)
                            flag = false;

                        if (flag == false)
                            break;
                    }
                }

                if (flag)
                    return 2;
                else
                    return 3;
            }
}

int Algebraic_Opeartion::highest_degree(vector<Term> input)
{
    int highest_exponent = 0;

    normalize_terms(input);

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

// Basic Operations //

Term Algebraic_Opeartion::add_term(Term A, Term B)
{
    int comparator_value = is_operable(A, B);

    Term result;

    if (comparator_value == 1) {
        result.isConstant = true;
        result.co_efficient = A.co_efficient + B.co_efficient;
    }
    else if (comparator_value == 2) {
        result.co_efficient = A.co_efficient + B.co_efficient;

        for (int i=0; i<A.get_variable_count(); ++i)
            result.variable_and_exponent.push_back(A.variable_and_exponent[i]);
    }

    return result;
}

Term Algebraic_Opeartion::sub_term(Term A, Term B)
{
    int comparator_value = is_operable(A, B);

    Term result;

    if (comparator_value == 1) {
        result.co_efficient = A.co_efficient - B.co_efficient;

        if (result.co_efficient != 0)
            result.isConstant = true;
    }
    else if (comparator_value == 2) {
        result.co_efficient = A.co_efficient - B.co_efficient;

        if (result.co_efficient != 0) {
            for (int i=0; i<A.get_variable_count(); ++i)
                result.variable_and_exponent.push_back(A.variable_and_exponent[i]);
        }
    }

    return result;
}

Term Algebraic_Opeartion::mul_term(Term A, Term B)
{
    int comparator_value = is_operable(A, B);

    Term result;

    if (comparator_value > -1) {
        result.co_efficient = A.co_efficient * B.co_efficient;

        for (int i=0; i<A.get_variable_count(); ++i)
            result.variable_and_exponent.push_back(A.variable_and_exponent[i]);

        for (int i=0; i<B.get_variable_count(); ++i)
            result.variable_and_exponent.push_back(B.variable_and_exponent[i]);

        shroten_terms(result);
    }

    return result;
}

Term Algebraic_Opeartion::div_term(Term A, Term B)
{
            int comparator_value = is_operable(A, B);

            Term result;
            int temp_fraction[2];
            pair <string, int> temp_pr;

            Handle_Fractions reduce_fraction;

            if (comparator_value > -1) {

                if(A.co_efficient % B.co_efficient != 0) {

                    temp_fraction[0] = A.co_efficient;
                    temp_fraction[1] = B.co_efficient;

                    reduce_fraction.start(temp_fraction);

                    if (temp_fraction[1] < 0 && temp_fraction[0] > 0) {
                        temp_fraction[0] *= -1;
                        temp_fraction[1] *= -1;
                    }

                    result.isFraction = true;
                    result.co_efficient_fraction[0] = temp_fraction[0];
                    result.co_efficient_fraction[1] = temp_fraction[1];
                }
                else {
                    result.co_efficient = A.co_efficient / B.co_efficient;
                }

                for (int i=0; i<A.get_variable_count(); ++i)
                    result.variable_and_exponent.push_back(A.variable_and_exponent[i]);

                for (int i=0; i<B.get_variable_count(); ++i) {
                    // result.variable_and_exponent.push_back(B.variable_and_exponent[i]);

                    temp_pr.first = B.variable_and_exponent[i].first;
                    temp_pr.second = -1 * B.variable_and_exponent[i].second;

                    result.variable_and_exponent.push_back(temp_pr);
                }

                shroten_terms(result);

                for (int i=0; i < result.get_variable_count(); ++i) {

                    if (result.variable_and_exponent[i].second == 0){
                        result.variable_and_exponent.erase( result.variable_and_exponent.begin() + i);
                        --i;
                    }
                }
            }

            return result;
}

// Normalizing utility functions //

void Algebraic_Opeartion::shroten_terms(Term &container)
{
            if (container.get_variable_count() <= 0)
                return;

            /* Initial sorting between variables to smoothen the later calculations */

            sort(container.variable_and_exponent.begin(), container.variable_and_exponent.end());

            pair<string, int> pr = container.variable_and_exponent[0];
            vector< pair<string, int> > temp_container;

            for(size_t i=1; i<container.variable_and_exponent.size(); ++i) {
                if (pr.first.compare(container.variable_and_exponent[i].first) != 0) {
                    temp_container.push_back(pr);

                    pr.first = container.variable_and_exponent[i].first;
                    pr.second = container.variable_and_exponent[i].second;
                } else {
                    pr.second += container.variable_and_exponent[i].second;
                }
            } 	temp_container.push_back(pr);

            container.variable_and_exponent.clear();
            container.variable_and_exponent.assign(temp_container.begin(), temp_container.end());
}

void Algebraic_Opeartion::normalize_terms(vector<Term> &container)
{
    for (size_t i=0; i < container.size(); ++i) {
        shroten_terms(container[i]);
    }
}

Term Algebraic_Opeartion::multiply_operator(Term op_a, Term op_b)
{
    Term returnVal;
    returnVal.reset();

    if (op_a.isOperator == true && op_b.isOperator == true) {
        returnVal.isOperator = true;

        if (op_a.awperator[0] == op_b.awperator[0])
            returnVal.awperator = "+";
        else
            returnVal.awperator = "-";
    }

    return returnVal;
}

bool Algebraic_Opeartion::compare_term(Term term1, Term term2)
{
    bool isEqual = true;

    if (term1.isBrace == term2.isBrace)
        if (term1.brace.compare(term2.brace) != 0)
            isEqual = false;
    else	isEqual = false;

    if (term1.isOperator == term2.isOperator)
        if (term1.awperator.compare(term2.awperator) != 0)
            isEqual = false;
    else	isEqual = false;

    if (term1.isEqualSign != term2.isEqualSign)
        isEqual = false;

    if (term1.isConstant == term2.isConstant)
        if (term1.co_efficient != term2.co_efficient)
            isEqual = false;
        else {
            shroten_terms(term1);
            shroten_terms(term2);

            if (term1.get_variable_count() != term2.get_variable_count())
                isEqual = false;
            else {
                // bool isVariableEqual = true;
                for (int i=0; i<term1.get_variable_count(); ++i) {
                    if (term1.variable_and_exponent[i].first[0] != term2.variable_and_exponent[i].first[0]) {
                        isEqual = false;
                        break;
                    }

                    if (term1.variable_and_exponent[i].second != term2.variable_and_exponent[i].second) {
                        isEqual = false;
                        break;
                    }
                }
            }
        }
    else	isEqual = false;

    return isEqual;
}

bool Algebraic_Opeartion::compare_line(vector<Term> line1, vector<Term> line2)
{
    bool isEqual = true;

    if (line1.size() != line2.size())
        isEqual = false;
    else {
        for (int i=0; i < line1.size(); ++i) {
            if (compare_term(line1[i], line2[i])){
                isEqual = false;
                break;
            }
        }
    }

    return isEqual;
}
