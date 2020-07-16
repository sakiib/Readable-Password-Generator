#include <bits/stdc++.h>
using namespace std;

std::mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline string process_words(string word) {
    string processed_word = "";
    int length = (int)word.size();
    for (int i = 0; i < length; i++) {
        if (isalpha(word[i])) {
            if (isupper(word[i])) word[i] = tolower(word[i]);
            processed_word.push_back(word[i]);
        }
    }
    return processed_word;
}

inline int get_random_number_in_range(int from, int to) {
    return rng() % (to - from + 1) + from;
}

string get_random_password(int password_lenght) {
    string random_password = "";
    for (int i = 0; i < password_lenght; i++) {
        int character_id = get_random_number_in_range(0, 25);
        assert(character_id >= 0 && character_id <= 25);
        char character = (character_id + 'a');
        random_password.push_back(character);
    }
    return random_password;
}

int cnt[26][26];
int total_character_after[26];
int first_character[26];

void calculate_count(vector <string> &words) {
    memset(cnt, 0, sizeof(cnt));
    int sz = (int)words.size();
    for (int i = 0; i < sz; i++) {
        string cur_word = words[i];
        int length = (int)cur_word.size();
        for (int j = 0; j < length - 1; j++) {
            cnt[cur_word[j] - 'a'][cur_word[j + 1] - 'a']++;
            if (j == 0) first_character[cur_word[j] - 'a']++;
        }
    }
    for (int cur = 0; cur < 26; cur++) {
        for (int next = 0; next < 26; next++) {
            total_character_after[cur] += cnt[cur][next];
        }
    }
}

int get_current_char(int previous_index) {
    int tot = total_character_after[previous_index];
    int num = get_random_number_in_range(0, tot);
    for (int next_char = 0; next_char < 26; next_char++) {
        if (num < cnt[previous_index][next_char]) return next_char;
        else num -= cnt[previous_index][next_char];
    }
    assert(false);
    return -1;
}

int get_first_character_index() {
    int total_character_at_first_pos = 0;
    for (int i = 0; i < 26; i++) total_character_at_first_pos += first_character[i];
    int num = get_random_number_in_range(0, total_character_at_first_pos);
    for (int cur_char = 0; cur_char < 26; cur_char++) {
        if (num < first_character[cur_char]) return cur_char;
        else num -= first_character[cur_char];
    }
    assert(false);
    return -1;
}

string get_readable_password(int password_length, bool capitalize = false, bool special_char = false) {
    string password = "";
    for (int i = 0; i < password_length; i++) {
        if (i == 0) {
            int character_idx = get_first_character_index();
            password.push_back(char(character_idx + 'a'));
        }
        else {
            int prev_character_idx = int(password[i - 1] - 'a');
            int cur_character_idx = get_current_char(prev_character_idx);
            assert(cur_character_idx >= 0 && cur_character_idx <= 25);
            password.push_back(char(cur_character_idx + 'a'));
        }
    }
    if (capitalize) password[0] = toupper(password[0]);
    if (special_char) password[get_random_number_in_range(1, password_length - 1)] = '*';
    assert(password_length == (int)password.size());
    return password;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("words-list.txt", "r", stdin);
    srand(time(0));

    string word;
    vector <string> words;

    while (cin >> word) {
        words.push_back(process_words(word));
    }

    int password_length = 10;
    cout << "just a random password: " << get_random_password(password_length) << "\n";

    calculate_count(words);

    cout << "more readable password: " << get_readable_password(password_length, true, false) << "\n";
    return 0;
}
