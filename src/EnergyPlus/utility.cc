//Geof Sawaya, 2014, LBL & DOE

#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include "utility.hh"

#include <DataHeatBalance.hh>
#include <DataSurfaces.hh>
#include <DataHeatBalSurface.hh>
#include <HeatBalanceIntRadExchange.hh>

namespace EppPerformance
{

extern "C" {
#include <unistd.h>
}

const int Perf_Thread_Count = Utility::getProcElementCount();

long
Utility::getL1CacheLineSize(){
  return sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
}

int
Utility::getProcElementCount(){
  std::ifstream f("/proc/cpuinfo");
  std::string line;
  int count = 0;
  while (getline(f, line)){
  if (line.find("processor") != std::string::npos) 
    ++count;
  }
  return count;
}

void
Utility::doDataDump(){
  using namespace EnergyPlus::DataHeatBalance;
  using namespace EnergyPlus::DataSurfaces;
  using namespace EnergyPlus::DataHeatBalSurface;
	using namespace EnergyPlus::DataViewFactorInformation;

	static bool numhit = 0;
	const int max(100);
	if (numhit > max){
		return;
	}else{
		++numhit;
	}
  std::ofstream file;
  file.open("data_dump.txt");

	// file << "HeatBalanceIntRadExchange::LoadBalanceVector" << std::endl;
	// for(auto i : EnergyPlus::HeatBalanceIntRadExchange::LoadBalanceVector){
	// 	file << i << ", ";
	// }
	// file << std::endl;

	// file << "ZoneInfo<ZoneViewFactorInformation> owner, (), (*surfBegin)(), (*surfBegin)(false), " <<
	// 	"(*surfEnd-1)(), (*surfEnd-1)(false), shadeChanged" << std::endl;
	// for(auto zi : ZoneInfo){
	//   auto surfEnd = zi.surfEnd;
	//   --surfEnd;
	// 	file << zi.owner << "," << zi() << "," << (*zi.surfBegin)() << "," << (*zi.surfBegin)(false) <<
	// 		"," << (*surfEnd)() << "," << (*surfEnd)(false) << "," << zi.shadeChanged << std::endl;
	// }

	// file << "VfSurfaces<reSurface> (), (false), zone, temp, emiss, isWindow" << std::endl;
	// for(auto vfs : VfSurfaces){
	// 	file << vfs() << "," << vfs(false) << "," << vfs.zone << "," << vfs.temperature << "," <<
	// 		vfs.emissivity << "," << vfs.isWindow << std::endl;
	// }

  // file << "ConstrWin<WindowAbsThermLay>: TypeIsWindow, InsideAbsorpThermal, TotGlassLayers" << std::endl;
  // for(auto cs : ConstrWin){
  //   file << cs.TypeIsWindow << "," << cs.InsideAbsorpThermal << "," <<
  //     cs.TotGlassLayers << std::endl;
  // }

  // file << "ZoneSpecs: SurfaceFirst, SurfaceLast" << std::endl;
  // for(auto zs : ZoneSpecs){
  //   file << zs.SurfaceFirst << "," << zs.SurfaceLast << std::endl;
  // }

  // file << "SurfaceRadiantWin: Shadingflag, ExtIntShadePrevTS, MovableSlats, OriginalClass, EffGlassEmiss, ThetaFace, EffShBlindEmiss" 
  //      << std::endl;
  // for(auto srw : SurfaceRadiantWin){
  //   file << srw.getShadingFlag() << "," // << srw.ExtIntShadePrevTS << "," << srw.MovableSlats FIXME (to test data)
	//  << "," << srw.OriginalClass << std::endl;
  //   file << "EffGlassEmiss:";
  //   for(int i = 1; i <=  srw.EffGlassEmiss.size1(); ++i){
  //     file << srw.EffGlassEmiss(i) << ",";
  //   }
  //   file << std::endl;
  //   file << "ThetaFace:";
  //   for(int i = 1; i <= srw.ThetaFace.size1(); ++i){
  //     file << srw.ThetaFace(i) << ",";
  //   }
  //   file << std::endl;
  //   file << "EffShBlindEmiss";
  //   for(int i = 1; i <= srw.EffShBlindEmiss.size1(); ++i){
  //     file << srw.EffShBlindEmiss(i) << ",";
  //   }
  //   file << std::endl;
  // }

  // file << "Construction" << std::endl;
  // for(auto c : Construction){
  //   file << c << std::endl;
  // }

  file << "NetLWRadToSurf" << std::endl;
  for(auto r : NetLWRadToSurf){
    file << r << std::endl;
  }

  file << "IRfromParentZone" << std::endl;
  for(auto ir : IRfromParentZone){
    file << ir << std::endl;
  }
  file.flush();
}
}