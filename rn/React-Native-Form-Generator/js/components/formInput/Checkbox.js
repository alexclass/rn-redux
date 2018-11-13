import React, { Component, PropTypes } from 'react'
import {
  View,
  Text,
  StyleSheet,
} from 'react-native'
import { CheckBox } from 'native-base'
import { Grid, Col, Row } from 'react-native-easy-grid'

const styles = StyleSheet.create({
  wrapper: {
    flex: 1,
  },
  label: {
    color: 'rgb(161, 176, 195)',
    fontSize: 14,
    fontWeight: '500',
  },
  checkboxLabel: {
    left: 10,
    color: 'rgb(35, 38, 61)',
    fontSize: 16,
    fontWeight: '500'
  }
})

const Checkbox = (props) => {
  return (
    <View style={styles.wrapper}>
      <Text style={styles.label}>{props.label}</Text>
      <Grid>
        {props.options.map((item, i) => {
          return (<Col key={`${props.id}${i}`}>
            <Row style={{ alignItems: 'center', paddingTop: 14 }}>
              <CheckBox {...props}
                onPress={() => props.selectedValue(item)}
                checked={ props.onChecked === item ? true : false }
                theme={{ checkboxBgColor: '#00BE9C', checkboxSize: 20, checkboxTickColor: '#fff', }} />
              <Text style={styles.checkboxLabel}>{item}</Text>
            </Row>
          </Col>)
        })}
      </Grid>
    </View>
  )
}

Checkbox.propTypes = {
  label: PropTypes.string.isRequired,
  options: PropTypes.array.isRequired
}

export default Checkbox
