/* @flow */

import React, { Component } from 'react'
import {
  View,
  Text,
  Image,
  StyleSheet,
  TouchableOpacity
} from 'react-native'
import { Header, Title, Button, Picker, } from 'native-base'

const Item = Picker.Item

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
  picker: {
    top: -4,
    left: -8,
    width: 400,
    justifyContent: 'flex-start',
  },
  pickerContainer: {
    flexDirection: 'row',
  },
  rightChavron: {
    alignItems: 'flex-end',
    justifyContent: 'center',
  },
  chavronIcon: {
    right: 5,
    justifyContent: 'flex-start',
  },
})

const DropdownPicker = (props) => {
  return (
    <View style={styles.wrapper}>
      <Text style={styles.label}>{props.label}</Text>
      <View style={styles.pickerContainer}>
        <Picker style={styles.picker} headerComponent={
          <Header>
            <Button transparent>Cancel</Button>
            <Title>{props.label}</Title>
          </Header>}
          mode="dropdown"
          {...props}>
          {props.options.map((item, i) => <Item key={`${props.id}${i}`} label={item} value={`${item}`} />)}
        </Picker>
        <View style={styles.rightChavron}>
          <Image source={require('../../../img/ic_back.png')}
            resizeMode='center'
            style={styles.chavronIcon} />
        </View>
      </View>
    </View>
  )
}

export default DropdownPicker
