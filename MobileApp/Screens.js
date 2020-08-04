import React, {Component} from "react";
import { View, Text, StyleSheet, Button, ScrollView,FlatList, TouchableOpacity, TouchableHighlight } from "react-native";
import { Provider } from 'react-redux';
import { createStore, applyMiddleware, } from 'redux';
import rootReducer from './reducers/index';
import { BleManager, BleError } from "react-native-ble-plx";
import thunk from 'redux-thunk';
//import {Container} from 'native-base';



const Manager = new BleManager();

const store = createStore(rootReducer, applyMiddleware(thunk.withExtraArgument(Manager)));

//Now starts the initial scan of the BLe

export const startScan = () => {
    return (dispatch, getState, Manager) => {
        const subscription = Manager.onStateChange((state) => {
            if (state === 'PoweredOn') {
                dispatch(scan());
                subscription.remove();
            }
        }, true);
    };
}

export const scan = () => {
    return (dispatch, getState, Manager) => {
        Manager.startDeviceScan(null, null, (error, device) =>  {
            dispatch(changeStatus("Scanning"));
           if(error) {
               console.log(error);
           }
           if(device !== null){
               dispatch(addBLE(device));
           }
        });
    }
}

export const connectDevice = (device) => {
    return (dispatch, getState, Manager) => {
        dispatch(changeStatus("Connecting"));
        DeviceManager.stopDeviceScan()
         device.connect()
            .then((device) => {
                dispatch(changeStatus("Discovering"));
                let characteristics = device.discoverAllServicesAndCharacteristics()
                return characteristics;
            })
            .then((device) => {
                dispatch(changeStatus("Setting Notifications"));
                return device;
            })
            .then((device) => {
                dispatch(changeStatus("Listening"));
                dispatch(connectedDevice(device))
                return device;
            }, (error) => {
                console.log(this._logError("SCAN", error));
                //return null;
            
            })
    }
}

export const connectedDevice = (device) => ({
    type: "CONNECTED_DEVICE",
    connectedDevice: device
});

export const changeStatus = (status) => ({
    type: "CHANGE_STATUS",
    status: status
});

class BLE extends Component {

    constructor(props)
    {
        super(props);
        this.props.startScan();
    }

    onsSelected = (id) => {

    }

    handleClick = (device) => {
        this.props.connectDevice(device);
    }

    _renderItem = ({item}) => (
        <Text>{item.name}</Text>
    );
}


export const Home = ({ navigation }) => {


    
    return (
    <ScrollView
    contentInsetAdjustmentBehavior="automatic"
    style = {styles.scrollView}
    >    
        <View style = {styles.container}>
        
            <Text style = {styles.sectionTitle}>Welcome to ACA</Text>
            
        </View>
        <View style = {styles.container}>
        <Text style = {styles.sectionDescription}>The first step in using the ACA is 
            connecting your phone via BlueTooth.  </Text>

        </View>
        <View style = {styles.container}>
            
        </View>
    </ScrollView>    
    )
}

export const Controller = ({ navigation }) => {
    return (
    <ScrollView
    contentInsetAdjustmentBehavior="automatic"
    style = {styles.scrollView}
    >  
        <View style = {styles.container}>
        
            <Text style = {styles.sectionTitle}>Page 2</Text>

        </View>
    </ScrollView>      
    )
}


const styles = StyleSheet.create({
    container:
    {
        marginTop: 15,
        paddingHorizontal: 10,
    },

    sectionDescription:
    {
     // flex: 1,
     // justifyContent: 'center',
      //alignItems: 'center',
      textAlign: 'center',
      backgroundColor: '#5D7AA3',
      fontSize: 16,
      color: 'white',
      fontWeight: 'bold',
      //marginTop: ,
      paddingHorizontal: 10
    },
  
    sectionTitle:
    {
      color: 'white',
      textAlign: 'center',
      fontWeight : 'bold',
      fontSize: 45,
      marginTop: 40
    },
    scrollView:
    {
        backgroundColor: '#5D7AA3',
    }
  });