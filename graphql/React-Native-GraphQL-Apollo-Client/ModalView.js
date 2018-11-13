/**
 * BY THUNDERBIRD7
 * FoolStack Developer
 */

import React, { Component, PropTypes } from 'react'
import {
  StyleSheet,
  Text,
  View,
  Modal, 
  TouchableHighlight,
  TouchableOpacity,
  ScrollView
} from 'react-native'
import { 
  Container, 
  Content, 
  Header, 
  Title, 
  H1,
  Button,
} from 'native-base'

const styles = StyleSheet.create({
  container: {
    flex:1,
    justifyContent: 'center',
    paddingTop: 100,
    paddingBottom: 100,
    paddingLeft: 20,
    paddingRight: 20,
    backgroundColor: 'rgba(0, 0, 0, 0.8)'
  },
  modal: {
    backgroundColor: 'floralwhite', 
    padding: 10, 
    borderRadius: 10,
  }
})

const ModalView = (props) => {
  return (
      <Modal
        animationType={"fade"}
        transparent={true}
        visible={props.visible} >
        <View style={styles.container}>
        <ScrollView style={styles.modal}>
          <H1>{props.title}</H1>
            <Text>{props.detail}</Text>
        </ScrollView>
          <View style={{top: 20}}>
            <Button block danger onPress={() => props.onDismiss()}>Close</Button> 
          </View>  
        </View>
      </Modal>
  )
}

export default ModalView