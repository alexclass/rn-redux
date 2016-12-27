import React from 'react';
import { View } from 'react-native';

const CardSection = (props) => {
  const { constainerStyle } = styles;
  return (
    <View style={constainerStyle}>
      {props.children}
    </View>
  );
};

const styles = {
  constainerStyle: {
    borderBottomWidth: 1,
    padding: 5,
    backgroundColor: '#fff',
    justifyContent: 'flex-start',
    flexDirection: 'row',
    borderColor: '#ddd',
    position: 'relative'
  }
};

export  { CardSection };
