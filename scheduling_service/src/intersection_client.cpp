
#include "intersection_client.h"
#include "OAIDefaultApi.h"
#include <QTimer>
#include <QEventLoop>
#include "OAIHelpers.h"

void intersection_client::call()
{
  OAIDefaultApi apiInstance;

  QEventLoop loop;
  connect(&apiInstance, &OAIDefaultApi::getIntersectionInfoSignal, [&](OAIIntersection_info int_info)
          {

<<<<<<< HEAD
            intersection_name = int_info.getName().toStdString();
            intersection_id = int_info.getId();
            spdlog::debug("intersection name: {0}", intersection_name);
            spdlog::debug("intersection id: {0}", intersection_id);
=======
            qDebug() << "Intersection name: " <<  int_info.getName();
            qDebug() << "Intersection id: "   << int_info.getId();
            intersection_name = int_info.getName().toStdString();
            intersection_id = int_info.getId();
>>>>>>> the intersection_client class has been added. the osm class must be removed!

            /* entry lanes */
            int count = 0;
            QList<OpenAPI::OAILanelet_info> entry_lanelets = int_info.getEntryLanelets(); 
            for(QList<OpenAPI::OAILanelet_info>::iterator itr = entry_lanelets.begin(); itr != entry_lanelets.end(); itr++ )
            {
<<<<<<< HEAD
=======
              qDebug() << "entry lanelet ID: "   << itr->getId();
              qDebug() << "Speed Limit: " << itr->getSpeedLimit();
>>>>>>> the intersection_client class has been added. the osm class must be removed!
              lane_information li;
              li.id = to_string(itr->getId());
              li.index = count;
              li.type = "entry";
<<<<<<< HEAD
              li.length = itr->getLength();
              /* the unit of received speed limit from the intersection model is mile/hr
              *  but the unit of speed limit used in the scheduling_service is meter/sec
              */
              li.speed_limit = itr->getSpeedLimit() * 0.44704;
=======
              li.direction = "straight";
              li.length = itr->getLength();
              li.speed_limit = itr->getSpeedLimit();
>>>>>>> the intersection_client class has been added. the osm class must be removed!
              li.priority = -1;
              lane_info[li.id] = li;
              lane_id_all.push_back(li.id);
	          	lane_id_entry.push_back(li.id);
              count += 1;
<<<<<<< HEAD

              spdlog::debug("entry lanelet ID: {0}", li.id);
              spdlog::debug("Speed Limit (m/s): {0}", li.speed_limit);
              spdlog::debug("Length (m): {0}", li.length);
=======
>>>>>>> the intersection_client class has been added. the osm class must be removed!
            }

            /* exit\departure lanes */
            QList<OpenAPI::OAILanelet_info> departure_lanelets = int_info.getDepartureLanelets();
            for(QList<OpenAPI::OAILanelet_info>::iterator itr = departure_lanelets.begin(); itr != departure_lanelets.end(); itr++ )
            {
<<<<<<< HEAD
=======
              qDebug() << "departure lanelet ID: "   << itr->getId();
              qDebug() << "Speed Limit: " << itr->getSpeedLimit();
>>>>>>> the intersection_client class has been added. the osm class must be removed!
              lane_information li;
              li.id = to_string(itr->getId());
              li.index = count;
              li.type = "exit";
<<<<<<< HEAD
              li.length = itr->getLength();
              /* the unit of received speed limit from the intersection model is mile/hr
              *  but the unit of speed limit used in the scheduling_service is meter/sec
              */
              li.speed_limit = itr->getSpeedLimit() * 0.44704;
=======
              li.direction = "straight";
              li.length = itr->getLength();
              li.speed_limit = itr->getSpeedLimit();
>>>>>>> the intersection_client class has been added. the osm class must be removed!
              li.priority = -1;
              lane_info[li.id] = li;
              lane_id_all.push_back(li.id);
	          	lane_id_exit.push_back(li.id);
              count += 1;
<<<<<<< HEAD

              spdlog::debug("departure lanelet ID: {0}", li.id);
              spdlog::debug("Speed Limit (m/s): {0}", li.speed_limit);
              spdlog::debug("Length (m): {0}", li.length);
=======
>>>>>>> the intersection_client class has been added. the osm class must be removed!
            } 

            /* link lanes */
            QList<OpenAPI::OAILanelet_info> link_lanelets = int_info.getLinkLanelets(); 
<<<<<<< HEAD
            for(QList<OpenAPI::OAILanelet_info>::iterator itr = link_lanelets.begin(); itr != link_lanelets.end(); itr++ )
            {
=======
            for(QList<OpenAPI::OAILanelet_info>::iterator itr = departure_lanelets.begin(); itr != departure_lanelets.end(); itr++ )
            {
              qDebug() << "departure lanelet ID: "   << itr->getId();
              qDebug() << "Speed Limit: " << itr->getSpeedLimit();
>>>>>>> the intersection_client class has been added. the osm class must be removed!
              lane_information li;
              li.id = to_string(itr->getId());
              li.index = count;
              li.type = "link";
<<<<<<< HEAD
              li.length = itr->getLength();
              /* the unit of received speed limit from the intersection model is mile/hr
              *  but the unit of speed limit used in the scheduling_service is meter/sec
              */
              li.speed_limit = itr->getSpeedLimit() * 0.44704;

              /* each link's priority depends on its direction. but since currently the lane directions are not available, all links are assumed to have the same priority 1 */
              li.priority = 1;
              spdlog::debug("departure lanelet ID: {0}", li.id);
              spdlog::debug("Speed Limit (m/s): {0}", li.speed_limit);
              spdlog::debug("Length (m): {0}", li.length);

              
              spdlog::debug("conflict lanelets of lanelet {0}:", li.id);
              QList<qint32> conflict_lanelets = itr->getConflictLaneletIds();
              for(QList<qint32>::iterator inner_itr = conflict_lanelets.begin(); inner_itr != conflict_lanelets.end(); inner_itr++ )
              {
                    li.conflicting_lane_id.push_back(to_string(*inner_itr));
                    spdlog::debug("lanelet {0}", li.conflicting_lane_id.back());
=======
              // li.direction = itr->getDirection();
              li.length = itr->getLength();
              li.speed_limit = itr->getSpeedLimit();

              li.priority = 1;
              // if (li.direction == "straight"){
              //   li.priority = 1;
              // }
              // else if (li.direction == "left"){
              //   li.priority = 2;
              // }
              // else if (li.direction == "right"){
              //   li.priority = 3;
              // }
              
              qDebug() << "Conflict lanelets: ";
              for(auto inner_itr = itr->getConflictLaneletIds().begin(); inner_itr != itr->getConflictLaneletIds().end(); inner_itr++ )
              {
                    qDebug() <<  *inner_itr;
                    li.conflicting_lane_id.push_back(to_string(*inner_itr));
>>>>>>> the intersection_client class has been added. the osm class must be removed!
              }
              lane_info[li.id] = li;
              lane_id_all.push_back(li.id);
	          	lane_id_link.push_back(li.id);
              count += 1;
            }

            lane_count = count;

            lane_conflict_status.resize(lane_count, vector<int>(lane_count));
            for (string lane_id1 : lane_id_link){
<<<<<<< HEAD
              // qDebug() << "lane ID: " << QString::fromStdString(lane_id1);
              for (string lane_id2 : lane_info[lane_id1].conflicting_lane_id){
                // qDebug() << "has conflict with: " << QString::fromStdString(lane_id2);
=======
              for (string lane_id2 : lane_info[lane_id1].conflicting_lane_id){
>>>>>>> the intersection_client class has been added. the osm class must be removed!
                lane_conflict_status[lane_info[lane_id1].index][lane_info[lane_id2].index] = 1;
              }
              lane_conflict_status[lane_info[lane_id1].index][lane_info[lane_id1].index] = 1;
            }

            loop.quit(); });

  connect(&apiInstance, &OAIDefaultApi::getIntersectionInfoSignalE, [&](OAIIntersection_info, QNetworkReply::NetworkError, QString error_str)
          {
<<<<<<< HEAD
            string error_str_print = error_str.toStdString();
            spdlog::critical("Error happened while issuing request : {0}", error_str_print);
=======
            qDebug() << "Error happened while issuing request : " << error_str;
>>>>>>> the intersection_client class has been added. the osm class must be removed!
            loop.quit(); });

  apiInstance.getIntersectionInfo();

  QTimer::singleShot(5000, &loop, &QEventLoop::quit);
  loop.exec();
}

<<<<<<< HEAD
/* */
string intersection_client::get_intersectionName(){return intersection_name;}

/* */
int intersection_client::get_intersectionId(){return intersection_id;}
=======
>>>>>>> the intersection_client class has been added. the osm class must be removed!

/* */
int intersection_client::get_laneCount(){return lane_count;}

/* */
vector<string> intersection_client::get_laneIdAll(){return lane_id_all;}

/* */
vector<string> intersection_client::get_laneIdEntry(){return lane_id_entry;}

/* */
vector<string> intersection_client::get_laneIdExit(){return lane_id_exit;}

/* */
vector<string> intersection_client::get_laneIdLink(){return lane_id_link;}

/* */
int intersection_client::get_laneIndex(string lane_id){return lane_info[lane_id].index;}

/* */
string intersection_client::get_laneType(string lane_id){return lane_info[lane_id].type;}

<<<<<<< HEAD
=======
/* */
string intersection_client::get_laneDirection(string lane_id){return lane_info[lane_id].direction;}
>>>>>>> the intersection_client class has been added. the osm class must be removed!

/* */
double intersection_client::get_laneLength(string lane_id){return lane_info[lane_id].length;}

/* */
double intersection_client::get_laneSpeedLimit(string lane_id){return lane_info[lane_id].speed_limit;}

/* */
bool intersection_client::hasConflict(string lane_id1, string lane_id2){
	if(lane_conflict_status[lane_info[lane_id1].index][lane_info[lane_id2].index] == 1){
		return true;
	} else{
		return false;
	}
}

/* */
int intersection_client::get_lanePriority(string lane_id){return lane_info[lane_id].priority;}
