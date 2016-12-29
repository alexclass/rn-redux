'use strict';

import React from 'react';
import { AppRegistry, View, Text } from 'react-native';
import { Provider } from 'react-redux';
import { createStore } from 'redux';
import reducers from './reducers';


export default function native() {
    const App = () => {
        return (
            <Provider store={createStore(reducers)}>
                <View style={{ flex: 1 }}>
                  <Text>
                    Pointlook
                  </Text>
                </View>
            </Provider>
        );
    };


  AppRegistry.registerComponent('Pointlook', () => App);
}
