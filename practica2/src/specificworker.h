/*
 *    Copyright (C)2018 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
       \brief
       @author authorname
*/



#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <thread>
#include <chrono>
#include <genericworker.h>
#include <innermodel/innermodel.h>
#include <stdlib.h> 

class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
	SpecificWorker(MapPrx& mprx);
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);
	void stop(){
		std::this_thread::sleep_for( std::chrono::milliseconds(300000) );
 		differentialrobot_proxy->setSpeedBase(0, 0);
        	std::cout << "Saliendo" << std::endl;
		exit(0);
	}
   

public slots:
	void compute();

private:
	InnerModel *innerModel;
	int speed = 250;
	bool chooseSide = false;
	std::thread finish;
	bool triggerSet = false;
};

#endif
