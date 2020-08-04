import React, {Component} from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';
import {createAppContainer} from 'react-navigation';
import { createMaterialBottomTabNavigator } from '@react-navigation/material-bottom-tabs';
import Icon  from 'react-native-vector-icons/Ionicons';
import MaterialCommunityIcons from 'react-native-vector-icons/MaterialCommunityIcons';
import { Home, Controller } from './Screens';
import { Provider } from 'react-redux';
import { createStore,applyMiddleware } from 'redux';
import rootReducer from './reducers/index';
import thunk from 'redux-thunk';
import {BleManager} from 'react-native-ble-plx';


const Tabs = createMaterialBottomTabNavigator();
const HomeStack = createStackNavigator();
const ControllerStack = createStackNavigator();

const HomeStackScreen = createStackNavigator ({
  Home: {screen: Home}

});

let HomeNavigation = createAppContainer(HomeStackScreen);

const ControllerStackScreen = () => (
  <ControllerStack.Navigator>
    <ControllerStack.Screen name='Controller' component={Controller}
    options={{
      headerTintColor: 'white',
      headerStyle: {backgroundColor: '#394B64'},
    }} />
  </ControllerStack.Navigator>
)

const Manager = new BleManager();

const store = createStore(rootReducer, applyMiddleware(thunk.withExtraArgument(Manager)));

export default class HomeScreen extends React.Component {
  
  render() {
  return (
    <Provider store={store}>
      <NavigationContainer>
        <Tabs.Navigator 
          activeColor= '#fff'
          labelStyle={{ fontSize: 12}}
          //style={{ backgroundColor: 'tomato'}}
          
          >
          
          <HomeNavigation />
          
          <Tabs.Screen name="Controller" component={ControllerStackScreen} 
          options={{
            tabBarLabel: 'Controller',
            tabBarIcon: ({ color }) => (
              <MaterialCommunityIcons name="google-controller" color={color} size={26} backgroundColor = "#1bcc3b" />
              ),
            }} />
        </Tabs.Navigator>
      </NavigationContainer>
    </Provider>
    );
  }
};



