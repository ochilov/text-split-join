//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <iostream>

//---------------------------------------------------------------------------
std::vector<std::string> split(const std::string& text, const std::string& separator = " ") {
	using std::size_t;
	using std::string::npos;

	std::vector<std::string> data;
	size_t sep_len = separator.length();
	if (!sep_len) {
		data.push_back(text);
		return data;
	}

	size_t len = text.length();
	size_t last_pos = 0, pos = 0;
	do {
		pos = text.find(separator, last_pos);
		data.push_back(text.substr(last_pos, pos - last_pos));
		last_pos = pos + sep_len;
	}
	while (pos != npos && last_pos < len);

	return data;
}

//---------------------------------------------------------------------------
std::string join(const std::vector<std::string>& data, const std::string& delim = " ") {
	std::string text;
	for (std::size_t i = 0u; i < data.size(); ++i) {
		if (i != 0) {
			text += delim;
		}
		text += data[i];
	}
	return text;
}

//---------------------------------------------------------------------------
std::ostream& operator <<(std::ostream& o, const std::string& text) {
	o << text.c_str();
	return o;
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	using namespace std;

	////////////////////////////////////////////////////////////////////////////
	cout << "split test data:" << endl;
	struct test_data_t {
		string sep, txt;
	} test_data[] = {
		{".", "i\'m.a.split.text"},
		{"|", "i\'m|a|split|text"},
		{"SPAM", "i\'mSPAMaSPAMsplitSPAMtext"},
	};
	for (unsigned i = 0, cnt = sizeof(test_data)/sizeof(test_data[0]); i < cnt; i++) {
		const test_data_t& item = test_data[i];
		cout << item.txt << ": [" << join(split(item.txt, item.sep), ", ") << "]" << endl;
	}
	cout << endl;


	////////////////////////////////////////////////////////////////////////////
	string separator = ".";
	cout << "split input text to by \'" << separator << "\':" << endl;
	string line;
	while (true) {
		cout << ">> ";
		getline(cin, line);
		if (line.empty() || line == "exit")
			break;
		cout << line << ": [" << join(split(line, separator), ", ") << "]" << endl;
	}
	return 0;
}
