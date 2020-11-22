#include "IntersectionInfo.h"

using Engine::Maths::IntersectionInfo;

IntersectionInfo::IntersectionInfo()
{

}

IntersectionInfo::IntersectionInfo(const IntersectionInfo& rhs)
{
	this->pointsOfIntersection = rhs.pointsOfIntersection;
}

IntersectionInfo::~IntersectionInfo()
{
}

IntersectionInfo IntersectionInfo::operator+(IntersectionInfo& rhs)
{
	IntersectionInfo result = IntersectionInfo();

	for (auto point : this->pointsOfIntersection)
	{
		result.pointsOfIntersection.push_back(point);
	}

	for (auto point : rhs.pointsOfIntersection)
	{
		result.pointsOfIntersection.push_back(point);
	}

	return result;
}

void IntersectionInfo::operator+=(const IntersectionInfo& rhs)
{
	for (auto point : rhs.pointsOfIntersection)
	{
		this->pointsOfIntersection.push_back(point);
	}
}

void IntersectionInfo::operator=(const IntersectionInfo& rhs)
{
	this->pointsOfIntersection = rhs.pointsOfIntersection;
}