import React, { Component } from 'react'
import {
  View,
  Text,
  Modal,
  Image,
  StyleSheet,
  DatePickerIOS,
  TouchableOpacity,
} from 'react-native'
import { Grid, Col, Row } from 'react-native-easy-grid'
import moment from 'moment'

class DatePicker extends Component {

  static defaultProps = {
    date: new Date(),
  }

  state = {
    date: this.props.date,
    pickerVisible: false,
    pickerLabel: 'Select',
  }

  onDateChange(date) {
    this.setState({ date: date, })
  }

  render() {
    console.log(`select date ${this.state.date}`)
    let formPayload = this.props.payload

    return (
      <View style={styles.wrapper}>
        <Text style={styles.label}>{formPayload.label}</Text>
        <View style={styles.pickerContainer}>
          <TouchableOpacity style={styles.picker}
            onPress={() => this.setState({ pickerVisible: true })}>
            <Text style={styles.pickerLabel}>{this.state.pickerLabel}</Text>
          </TouchableOpacity>
          <View style={styles.rightChavron}>
            <Image source={require('../../../img/ic_back.png')}
              resizeMode='center'
              style={styles.chavronIcon} />
          </View>
        </View>
        <Modal
          animationType={"fade"}
          transparent={true}
          visible={this.state.pickerVisible} >
          <View style={styles.modal}>
            <View style={styles.datePicker} >
              <DatePickerIOS
                date={this.state.date}
                mode="date"
                maximumDate={this.props.date}
                onDateChange={this.onDateChange.bind(this)} />
              <View style={{ height: 40 }}>
                <Grid>
                  <Col>
                    <TouchableOpacity onPress={() => this.setState({ pickerVisible: false })} style={styles.pickerButton}>
                      <Text style={styles.cancelButtonLabel}>Cancel</Text>
                    </TouchableOpacity>
                  </Col>
                  <Col>
                    <TouchableOpacity onPress={() => this.setState({ pickerLabel: moment(this.state.date).format("DD MMMM YYYY"), pickerVisible: false })} style={styles.pickerButton}>
                      <Text style={styles.okButtonLabel}>OK</Text>
                    </TouchableOpacity>
                  </Col>
                </Grid>
              </View>
            </View>
          </View>
        </Modal>
      </View>
    )
  }
}

const styles = StyleSheet.create({
  wrapper: {
    marginTop: 16,
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
    flex: 1,
    justifyContent: 'flex-start',

  },
  pickerLabel: {
    top: 4,
    fontSize: 16,
  },
  pickerContainer: {
    flexDirection: 'row',
  },
  rightChavron: {
    top: 4,
    justifyContent: 'flex-end',
  },
  chavronIcon: {
    right: 5,
  },
  modal: {
    flex: 1,
    justifyContent: 'center',
    paddingLeft: 20,
    paddingRight: 20,
    backgroundColor: 'rgba(0, 0, 0, 0.8)',
  },
  datePicker: {
    backgroundColor: 'white',
    height: 260,
    justifyContent: 'flex-start',
    borderRadius: 6,
  },
  pickerButton: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  okButtonLabel: {
    color: 'dodgerblue',
    fontWeight: '500',
    fontSize: 15
  },
  cancelButtonLabel: {
    color: 'red',
    fontWeight: '500',
    fontSize: 15
  },
})

export default DatePicker