import React, { component } from 'react'
import Checkbox from './containers/CheckboxWrapper'
import TextField from './containers/TextFieldWrapper'
import Picker from './containers/PickerWrapper'
import DatePicker from './components/formInput/DatePicker'

export default formGeneratorComponents = (data) => {
  let components = []
  data.forEach( (input, i) => {

    switch (input.type) {
      case 'choice':
        components.push(
          <Checkbox
            key={i}
            id={i}
            type={input.type}
            name={input.name}
            label={input.label}
            options={input.options} />)
        break
      case 'textfield':
        components.push(
          <TextField
            key={i}
            id={i}
            type={input.type}
            name={input.name}
            label={input.label}
            placeholder={input.placeholder} />)
        break
      case 'picker':
        components.push(
          <Picker
            key={i}
            id={i}
            type={input.type}
            name={input.name}
            label={input.label}
            options={input.options} />)
        break
      case 'date-picker':
        components.push(
          <DatePicker
            key={i}
            id={i}
            type={input.type}
            name={input.name}
            payload={input.payload} />)
        break
      default:
    }
  })

  return components
}
