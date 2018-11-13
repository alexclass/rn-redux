import React, { Component } from 'react'
import {
  StyleSheet,
  View,
} from 'react-native'
import DropdownPicker from '../components/formInput/Picker'

export default class PickerWrapper extends Component {

  state = {
    formData: null
  }

  constructor(props) {
    super(props)
  }

  componentDidMount() {
    const form = this.props
    switch (form.id) {
      case 5:
        this.setState({
          formData: {
            name: form.name,
            type: form.type,
            label: form.label,
            input: `${form.options[176]}`,
          },
          selectedValue: `${form.options[176]}`
        })
        break
      case 6:
        this.setState({
          formData: {
            name: form.name,
            type: form.type,
            label: form.label,
            input: `${form.options[213]}`,
          },
          selectedValue: `${form.options[213]}`
        })
        break
      default:
        this.setState({
          formData: {
            name: form.name,
            type: form.type,
            label: form.label,
            input: `${form.options[0]}`,
          },
          selectedValue: `${form.options[0]}`
        })
    }
  }

  _onValueChange(value) {
    const form = this.props
    let payload = {
      name: form.name,
      type: form.type,
      label: form.label,
      input: value,
    }
    this.setState({ formData: payload, selectedValue: value })
  }

  render() {
    // TODO:
    // Grab all default state to Redux
    return (
      <View style={{ marginTop: 16 }}>
        <DropdownPicker
          onValueChange={(value) => this._onValueChange(value)}
          label={this.props.label}
          id={this.props.id}
          options={this.props.options}
          selectedValue={this.state.selectedValue} />
      </View>
    )
  }
}