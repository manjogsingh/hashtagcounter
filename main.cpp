#include "Defs.h"
#include "FibonacciHeap.h"

PrintType pType = Console;

void printQuery(Map *inputData, int *array, int query) {
	Map printCopy = *inputData;
	for (int i = 0; i < query; i++) {
		for (MapIterator it = printCopy.begin(); it != printCopy.end(); ++it) {
			if (it->second == array[i]) {
				Log << "\t" << i + 1 << ". " << it->first << " => " << it->second << '\n';
				printCopy.erase(it);
				break;
			}
		}
	}
	Log << '\n';
}

void printQuery(OFStream *outputFile, Map *inputData, int *array, int query) {
	Map printCopy = *inputData;
	for (int i = 0; i < query; i++) {
		for (MapIterator it = printCopy.begin(); it != printCopy.end(); ++it) {
			if (it->second == array[i]) {
				String tag = String(it->first.begin() + 1, it->first.end());
				*outputFile << tag << ",";
				printCopy.erase(it);
				break;
			}
		}
	}
	long pos = outputFile->tellp();
	outputFile->seekp(pos - 1);
	outputFile->write("\n", 1);
	// *outputFile<<'\n';
}

int *runQuery(Map *inputData, const int query) {
	int *array = new int(query);

	Vector valueData;

	FibonacciHeap fHeap;

	for (MapIterator it = inputData->begin(); it != inputData->end(); ++it) {
		valueData.push_back(it->second);
	}

	for (int i = 0; i < valueData.size(); i++) {
		fHeap.insert(valueData[i]);
	}

	for (int i = 0; i < query; i++) {
		array[i] = fHeap.removeMaximum();
		// Log<<"\t\t"<<i<< ". "<<array[i]<<"\n";
	}

	return array;
}

void parseInputFile(IFStream *inputFile, OFStream *outputFile, Map *inputData) {
	char *line = new char[256];
	int count;
	int query;
	String hashtag;

	while (inputFile->getline(line, 256, '\n')) {
		if ((strcmp(line, "stop") || strcmp(line, "STOP")) == 0) {
			Log << "\n\tSTOPING...\n\n";
			break;
		} else if (isdigit(line[0])) {
			query = atoi(line);
			int *resultArray = new int(query);

			resultArray = runQuery(inputData, query);

			if (pType == Console) {
				printQuery(inputData, resultArray, query);
			} else {
				printQuery(outputFile, inputData, resultArray, query);
			}

			delete resultArray;
			inputData->clear();
			inputData = new Map();
		} else {
			char h[INT16_MAX];
			sscanf(line, "%s %d", h, &count);
			hashtag = String(h);

			PairCheck result;
			MapIterator it;

			result = inputData->insert(Pair(hashtag, count));
			if (!result.second) {
				it = inputData->find(hashtag);
				it->second += count;
			}
		}
	}
	delete[] line;
}

int main(int argc, char *argv[]) {
	if (argc < 2 || argc > 3) {
		Log_E << "\n\tUsage: ./hashtagcounter input.txt output.txt\n";
		Log_E << "\tExiting ...\n\n";
		exit(0);
	}

	IFStream *inputFile;
	inputFile = new IFStream(argv[1]);

	OFStream *outputFile;
	if (argv[2]) {
		pType = File;
		outputFile = new OFStream(argv[2]);
	} else {
		pType = Console;
	}

	Map *inputData;
	if (inputFile->is_open()) {
		inputData = new Map();
		parseInputFile(inputFile, outputFile, inputData);
	} else {
		Log_E << "\n\tInput File does not exsist\n";
		Log_E << "\tExiting ...\n\n";
		exit(0);
	}

	inputFile->close();
	if (pType == File)
		outputFile->close();

	inputData->clear();
	delete inputData;
	delete inputFile;
	delete outputFile;
	return 0;
}