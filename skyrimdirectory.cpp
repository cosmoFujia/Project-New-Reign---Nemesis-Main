#include "skyrimdirectory.h"

using namespace std;

DataPath::DataPath()
{
	namespace bf = boost::filesystem;
	bf::path path(bf::current_path());
	// bf::path path("E:\\C++\\Project 2\\Nemesis Main GUI\\data\\meshes");

	if (wordFind(path.string(), "\\Data\\") != NOT_FOUND)
	{
		while (true)
		{
			if (wordFind(path.parent_path().string(), "\\Data") == NOT_FOUND)
			{
				break;
			}

			path = path.parent_path();
		}

		dataPath = path.string();
	}
	else
	{
		ErrorMessage(1008);
		return;
	}
}

string DataPath::GetDataPath()
{
	return dataPath;
}