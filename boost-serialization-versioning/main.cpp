#include <boost/filesystem.hpp>


template<typename T>
class Loader
{
public:
	static T fetch(std::string filePath);
	static void save(std::string filePath, std::unique_ptr<T> resource);
private:

};


template<typename T>
std::unique_ptr<T> Loader<T>::fetch(std::string filePath)
{
	boost::filesystem::path file(filePath.c_str());
	if(boost::filesystem::exists(file))
	{
		std::unique_ptr<T> load_from_file{nullptr};

		std::ifstream inputStream(filePath);
		boost::archive::text_iarchive inputArchive(inputStream);

		inputArchive >> load_from_file;
		if(!load_from_file)
		{
			throw std::runtime_error();
		}

		inputStream.close();

		return load_from_file;
	}

	throw std::runtime_error();
}

template<typename T>
void Loader<T>::save(std::string filePath, std::unique_ptr<T>& resource)
{
	if(resource)
	{
		boost::filesystem::path file(filePath.c_str());
		if(boost::filesystem::exists(file))
		{
			std::ofstream outputStream(filePath);
			if(outputStream)
			{
				boost::archive::text_oarchive inputArchive(outputStream);

				outputArchive << resource;

				outputStream.close();
			}
			else
			{
				throw std::runtime_error();
			}
		}
	}
}

int main()
{

	std::unique_ptr<int> myInt {new int(5)};

	Loader::save<int>(myInt);
}

