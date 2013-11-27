/*
---------------------------------------------------------------------------

    This file is part of uHAL.

    uHAL is a hardware access library and programming framework
    originally developed for upgrades of the Level-1 trigger of the CMS
    experiment at CERN.

    uHAL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    uHAL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with uHAL.  If not, see <http://www.gnu.org/licenses/>.

      Marc Magrans de Abril, CERN
      email: marc.magrans.de.abril <AT> cern.ch

      Andrew Rose, Imperial College, London
      email: awr01 <AT> imperial.ac.uk

      Alessandro Thea, Rutherford Appleton Laboratory, Oxford
      email: alessandro.thea <AT> stfc.ac.uk

---------------------------------------------------------------------------
*/

#include "uhal/tests/tools.hpp"
#include "uhal/tests/DummyDerivedNode.hpp"
#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include <typeinfo>

using namespace uhal;

/*
// To Delete
void print_derived ( const std::string& connection, const std::string& id ) {

  ConnectionManager manager ( connection );
  HwInterface hw=manager.getDevice ( id );

  log( Notice(), "Plain node     : class attribute (user-level)");
  hw.getNode<tests::DummyParentNode>("DERIVEDNODE").printParameters();

  log( Notice(), "Module node 1. : inner class attribute (Level2)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE1").printParameters();

  log( Notice(), "Module node 1.1: inner class attribute with parameter override (Level2)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE1_1").printParameters();

  log( Notice(), "Module node 2. : 1-levels class structure and inner parameter override (Level2, Level1)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE2").printParameters();

  log( Notice(), "Module node 2.1: 1-levels class structure and outer parameter override (Level2, Level1)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE2_1").printParameters();

  log( Notice(), "Module node 3. : 2-levels class structure and inner parameter override (Level2, Level1)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE3").printParameters();

  log( Notice(), "Module node 3.1: 2-levels class structure and outer parameter override (Level2, Level1)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE3_1").printParameters();

  log( Notice(), "Module node 4. : class override (Level2, Level1)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE4").printParameters();

  log( Notice(), "Module node 4.1: class and parameter override (Level2, Level1)");
  hw.getNode<tests::DummyChildNode>("DERIVEDMODULE4_1").printParameters();

}
*/

/*
void derivednode_parameters ( const std::string& connection, const std::string& id ) {

  ConnectionManager manager ( connection );
  HwInterface hw=manager.getDevice ( id );

  // Check parameters overriding 
  boost::unordered_map<std::string,std::string> lPars;
  boost::unordered_map<std::string,std::string>::iterator iPar; 

  lPars = hw.getNode("DERIVEDNODE").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val1" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val2" );
  CACTUS_CHECK( ( iPar = lPars.find("arg3") ) != lPars.end() && iPar->second == "val3" );

  lPars = hw.getNode("DERIVEDMODULE1").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val1" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val2" );
  CACTUS_CHECK( ( iPar = lPars.find("arg3") ) != lPars.end() && iPar->second == "val3" );

  lPars = hw.getNode("DERIVEDMODULE2").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val1" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val2" );
  CACTUS_CHECK( ( iPar = lPars.find("arg3") ) != lPars.end() && iPar->second == "val3" );

  lPars = hw.getNode("DERIVEDMODULE2_1").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val107" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val207" );
  CACTUS_CHECK( ( iPar = lPars.find("arg3") ) != lPars.end() && iPar->second == "val3" );

  lPars = hw.getNode("DERIVEDMODULE3").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val1" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val2" );
  CACTUS_CHECK( ( iPar = lPars.find("arg3") ) != lPars.end() && iPar->second == "val3" );

  lPars = hw.getNode("DERIVEDMODULE3_1").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val107" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val207" );
  CACTUS_CHECK( ( iPar = lPars.find("arg3") ) != lPars.end() && iPar->second == "val3" );

  lPars = hw.getNode("DERIVEDMODULE4").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val1" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val2" );

  lPars = hw.getNode("DERIVEDMODULE4_1").getParameters();
  CACTUS_CHECK( ( iPar = lPars.find("arg1") ) != lPars.end() && iPar->second == "val107" );
  CACTUS_CHECK( ( iPar = lPars.find("arg2") ) != lPars.end() && iPar->second == "val207" );
  CACTUS_CHECK( ( iPar = lPars.find("arg3") ) != lPars.end() && iPar->second == "val3" );

}
*/

void derivednode_building ( const std::string& connection, const std::string& id ) {
  ConnectionManager manager ( connection );
  HwInterface hw=manager.getDevice ( id );
  using namespace std;

  // Check node casting
  CACTUS_CHECK( typeid( hw.getNode("SUBSYSTEM3.DERIVEDNODE") )    == typeid(tests::DummyParentNode) );
  CACTUS_CHECK( typeid( hw.getNode("SUBSYSTEM3.DERIVEDMODULE1") ) == typeid(tests::DummyChildNode) );
  CACTUS_CHECK( typeid( hw.getNode("SUBSYSTEM3.DERIVEDMODULE2") ) == typeid(tests::DummyChildNode) );
  CACTUS_CHECK( typeid( hw.getNode("SUBSYSTEM3.DERIVEDMODULE3") ) == typeid(tests::DummyChildNode) );
  CACTUS_CHECK( typeid( hw.getNode("SUBSYSTEM3.DERIVEDMODULE4") ) == typeid(tests::DummyChildNode) );
  CACTUS_CHECK( typeid( hw.getNode("SUBSYSTEM3.BADNODE") ) == typeid(uhal::Node) );
}

int main ( int argc,char* argv[] )
{

  std::map<std::string,std::string> params = tests::default_arg_parsing ( argc,argv );
  std::string connection_file = params["connection_file"];
  std::string device_id = params["device_id"];

  CACTUS_TEST( derivednode_building( connection_file, device_id ) );

  CACTUS_TEST_RESULT();
}
