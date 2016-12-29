import React, {Component} from 'react';
import { Text, View, TouchableWithoutFeedback, LayoutAnimation } from 'react-native';
import { connect } from 'react-redux';
import {CardSection} from './common';
import * as actions from '../actions';

class ListItem extends Component {
    componentWillUpdate() {
        LayoutAnimation.spring();
    }
    
    renderDescription() {
        console.log('1.ListItem renderDescription props: ', this.props);
        const { library, expanded } = this.props;
        console.log('2.ListItem renderDescription library.id: ',library.id,' expanded: ',expanded);
        if (expanded) {
            return (
                <CardSection>
                    <Text 
                        style={{ flex: 1, paddingLeft: 15, fontSize: 10 }}
                    >
                        {library.description}
                    </Text>
                </CardSection>
            );
        }
    }
    render () {
        console.log('1.ListItem render props: ', this.props);
        const { titleStyle } = styles;
        const { id, title } = this.props.library;

        return (
            <TouchableWithoutFeedback
                onPress={() => this.props.selectLibrary(id)}
            >
                <View>
                    <CardSection>
                        <Text style={titleStyle} >
                            {title}
                        </Text>
                    </CardSection>
                    {this.renderDescription()}
                </View>
            </TouchableWithoutFeedback>
        );
    }
}

const styles = {
    titleStyle: {
        fontSize: 18,
        paddingLeft: 15
    }
}

const mapStateToProps = (state, ownProps) => {
    console.log('1.ListItem mapStateToProps state: ', state,' ownProps: ', ownProps);
    const expanded = state.selectedLibraryId === ownProps.library.id;
    return { expanded };
}

export default connect(mapStateToProps, actions)(ListItem);