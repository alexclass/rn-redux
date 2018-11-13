import React, { Component } from 'react'
import {
  View,
  Text,
  StyleSheet,
  TextInput,
  TouchableOpacity,
} from 'react-native';

const styles = StyleSheet.create({

  wrapper: {
    height: 48,
    borderBottomColor: 'rgb(212, 220, 230)',
    borderBottomWidth: 1,
  },
  label: {
    color: 'rgb(161, 176, 195)',
    fontSize: 14,
    fontWeight: '500',
  },
  input: {
    flex: 1,
    height: 40,
    justifyContent: 'center',
    color: 'rgb(35, 38, 61)',
    fontSize: 16,
    fontWeight: '500',
  },
  rightButton: {
    position: 'absolute',
    top: -30,
    right: 0,
  },
  rightButtonText: {
    textAlign: 'right',
    width: 70,
    color: 'rgb(0, 186, 228)',
    fontSize: 16,
  },
})

const TextField = (props) => {
  return (
    <View style={styles.wrapper}>
      <Text style={styles.label}>{props.label}</Text>
      <TextInput {...props}
        style={styles.input}
        />
      {props.showRightButton ?
        <View style={{ marginRight: 5 }}>
          <TouchableOpacity
            {...props}
            style={styles.rightButton}>
            <Text style={styles.rightButtonText}>{props.rightButtonTitle}</Text>
          </TouchableOpacity>
        </View> : null}
    </View>
  )
}

export default TextField