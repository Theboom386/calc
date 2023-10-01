#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int get_inches(int feet, int inches) {
    return feet * 12 + inches;
}

vector<int> split_by_regex(const string& input, const regex& re) {
    vector<int> values;
    sregex_token_iterator it(input.begin(), input.end(), re, -1);
    sregex_token_iterator reg_end;

    for (; it != reg_end; ++it) {
        if (!it->str().empty()) {
            try {
                values.push_back(stoi(it->str()));
            } catch (invalid_argument&) {
                cout << "Invalid input. Enter valid integers for feet and inches separated by space, '-', '/', or '.'.\n";
                return {};
            }
        }
    }
    return values;
}

pair<int, int> get_distance_input(string prompt) {
    cout << prompt;
    string input_str;
    getline(cin, input_str);

    regex re("[ -/.]");
    vector<int> values = split_by_regex(input_str, re);

    if (values.size() == 1) {
        return {values[0], 0};
    } else if (values.size() == 2) {
        return {values[0], values[1]};
    } else {
        cout << "Invalid input format.\n";
        return {-1, -1};
    }
}

void print_difference(int feet1, int inches1, int feet2, int inches2, int difference) {
    string feet1_word = (feet1 == 1) ? "foot" : "feet";
    string inches1_word = (inches1 == 1) ? "inch" : "inches";
    string feet2_word = (feet2 == 1) ? "foot" : "feet";
    string inches2_word = (inches2 == 1) ? "inch" : "inches";
    string difference_word = (difference == 1) ? "inch" : "inches";

    int difference_feet = difference / 12;
    int difference_inches = difference % 12;
    string difference_feet_word = (difference_feet == 1) ? "foot" : "feet";
    string difference_inches_word = (difference_inches == 1) ? "inch" : "inches";

    cout << "First Distance: " << feet1 << " " << feet1_word << " " << inches1 << " " << inches1_word << endl;
    cout << "Second Distance: " << feet2 << " " << feet2_word << " " << inches2 << " " << inches2_word << endl;
    cout << "Difference in Inches: " << difference << " " << difference_word << endl;
    cout << "Difference in Ft-In: " << difference_feet << " " << difference_feet_word << " " << difference_inches << " " << difference_inches_word << endl;
}

void calculate_and_print_difference(int feet1, int inches1, int feet2, int inches2) {
    int total_inches1 = get_inches(feet1, inches1);
    int total_inches2 = get_inches(feet2, inches2);

    if (total_inches1 > total_inches2) {
        print_difference(feet1, inches1, feet2, inches2, total_inches1 - total_inches2);
    } else if (total_inches1 < total_inches2) {
        print_difference(feet2, inches2, feet1, inches1, total_inches2 - total_inches1);
    } else {
        cout << "Both distances are equal.\n";
    }
}

int main() {
    while (true) {
        cout << endl;
        auto [feet1, inches1] = get_distance_input("Enter the first distance (format: 'feet[separator]inches' where separator can be space, '-', '/', or '.'): ");
        cout << endl;
        auto [feet2, inches2] = get_distance_input("Enter the second distance (format: 'feet[separator]inches' where separator can be space, '-', '/', or '.'): ");
        cout << endl;

        if (feet1 == -1 || feet2 == -1) {
            continue;
        }

        calculate_and_print_difference(feet1, inches1, feet2, inches2);
        cout << endl;
    }
    return 0;
}
