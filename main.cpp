#include "tests.h"
#include "h/eval_apply.h"
#include "h/tokenizer.h"
#include "h/pretty_print.h"

#include <type_traits>
#include <utility>

/** /
auto main_str = constexpr_string(R"(
(car (list
    1 (+ 1 2)))
)");
/**/
auto main_str = constexpr_string(R"(
(cdr (list
    1 (+ 1 2)))
)");

using tokenization_result_w_whitespaces = decltype(tokenize(main_str)); // raw token list without the tokenized<...> wrapper
// remove whitespaces
using tokens = decltype(clean_whitespaces(tokenization_result_w_whitespaces{}));
// replace token_list<list<...>> with wrap<list<...>>
using clean_expression = typename replace_nested_list<tokens>::type; // convert list
// replace outer wrap<...> with tokenized<...>
using tb_evaluated = decltype(replace_wrapper(clean_expression{},tokenized{}));
// evaluate expression
using eval_result = decltype(IReval<init_env>(IRcar(tb_evaluated{})));


int main(){
    std::cout << ":::: string to parse ::::" << '\n';
    std::cout << main_str() << '\n';
    std::cout << '\n';

    /** /
    std::cout << ":::: tokenization_result_w_whitespaces ::::" << '\n';
    std::cout << replace_chars(demangle<tokenization_result_w_whitespaces>()) << '\n';
    std::cout << '\n';
    /**/

    std::cout << ":::: formatted tokenization result ::::" << '\n';
    std::cout << (replaceWhitespace(replace_chars(demangle<tokenization_result_w_whitespaces>()))) << std::endl;
    std::cout << '\n';
    
    /** /
    std::cout << ":::: cleaned ::::" << '\n';
    std::cout << replace_chars(demangle<tb_evaluated>()) << '\n';
    std::cout << '\n';
    /**/

    std::cout << ":::: eval res ::::" << '\n';
    std::cout << replace_chars(demangle<eval_result>()) << '\n';
    return 0;
}


// lambda is also missing

// eval wrap<list<...>>
// eval quote<wrap<list<..>>>
// eval wrap<list<..>>  quote does not matter here, probably eval is redundant when there is no quote
