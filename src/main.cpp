#include <iostream>
#include <fstream>
#include <cctype>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

constexpr auto INPUT_ARGS_COUNT = 3;

using WordToCountDictionary = unordered_map<string, unsigned int>;
using CountToWordsDictionary = unordered_map<unsigned int, vector<string>>;
using SortedCountToWordsDictionary = vector<pair<unsigned int, vector<string>*>>;

WordToCountDictionary ReadWords(ifstream & inputStream)
{
	WordToCountDictionary wordToCountDictionary;

	string wordBuf;
	using buf_iter = std::istreambuf_iterator<char>;
	const buf_iter eof;
	for (buf_iter it = inputStream; it != eof; ++it)
	{
		const auto symbol = tolower(static_cast<unsigned char>(*it));
		if (isalpha(symbol))
		{
			wordBuf += symbol;
		}
		else if (!wordBuf.empty())
		{
			++wordToCountDictionary[wordBuf];
			wordBuf.clear();
		}
	}

	return wordToCountDictionary;
}

CountToWordsDictionary GetCountToWordsDictionary(const WordToCountDictionary & wordToCountDictionary)
{
	CountToWordsDictionary countToWordsDictionary;
	for (const auto & [word, count] : wordToCountDictionary)
	{
		countToWordsDictionary[count].push_back(word);
	}

	return countToWordsDictionary;
}

SortedCountToWordsDictionary SortWordsByCount(CountToWordsDictionary & countToWordsDictionary)
{
	SortedCountToWordsDictionary sortedCountToWordsDictionary;
	sortedCountToWordsDictionary.reserve(countToWordsDictionary.size());

	for (auto & [count, words] : countToWordsDictionary)
	{
		sort(begin(words), end(words));
		sortedCountToWordsDictionary.push_back({ count, &words });
	}

	sort(begin(sortedCountToWordsDictionary), end(sortedCountToWordsDictionary),
		[] (const auto & left, const auto & right)
		{
			return left.first > right.first;
		});

	return sortedCountToWordsDictionary;
}

void PrintResults(ofstream & outputStream, const SortedCountToWordsDictionary & sortedCountToWords)
{
	for (const auto & [count, pWords] : sortedCountToWords)
	{
		assert(pWords != nullptr);
		for (const auto & word : *pWords)
		{
			outputStream << count << " " << word << endl;
		}
	}
}

int main(int _argc, char * _argv[])
{
	if (_argc != INPUT_ARGS_COUNT)
	{
		cerr << "Usage: " << _argv[0] << " <inputfile> <outputfile>" << endl;
		return 1;
	}

	const string inputFileName(_argv[1]);
	ifstream inputStream{ inputFileName };
	if (!inputStream)
	{
		cerr << "Cannot open input file: " << inputFileName << endl;
		return 2;
	}

	const string outputFileName(_argv[2]);
	ofstream outputStream{ outputFileName };
	if (!outputStream)
	{
		cerr << "Cannot create output file: " << outputFileName << endl;
		return 3;
	}

	const auto wordToCountDictionary = ReadWords(inputStream);
	auto countToWordsDictionary = GetCountToWordsDictionary(wordToCountDictionary);
	const auto sortedCountToWordsDictionary = SortWordsByCount(countToWordsDictionary);

	PrintResults(outputStream, sortedCountToWordsDictionary);

	inputStream.close();
	outputStream.close();

	cout << "Results were successfully written to file: \"" << outputFileName << "\"" << endl;

	return 0;
}
