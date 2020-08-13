#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_member.hpp>
#include <iostream>
#include <fstream>

class Player
{
public:
	Player() : m_name{}, m_level{0}, m_race{5} { }

	void setName(std::string name) { m_name = name; }
	void setLevel(int level) { m_level = level; }
	void setRace(int race) { m_race = race; }

	std::string getName() const { return m_name; }
	int getLevel() const { return m_level; }
	int getRace() const { return m_race; }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        // note, version is always the latest when saving
        ar  & m_name;
        ar  & m_level;
        ar  & m_race;
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
    		ar & m_name;
    		ar & m_level;
        if(version > 0)
            ar & m_race;
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
	std::string m_name;
	int m_level;
	int m_race;
};

BOOST_CLASS_VERSION(Player, 1)

int main()
{
	Player myPlayer;

	std::ifstream inputStream("aaron.txt");
	boost::archive::text_iarchive inputArchive(inputStream);

	inputArchive >> myPlayer;
	inputStream.close();

	std::ofstream outputStream("aaron.txt");
	boost::archive::text_oarchive outputArchive(outputStream);

	outputArchive << myPlayer;



}