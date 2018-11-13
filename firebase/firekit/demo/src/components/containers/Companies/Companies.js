import React, {Component} from 'react';
import _ from 'lodash';
import { connect } from 'react-redux';
import PropTypes from 'prop-types';
import muiThemeable from 'material-ui/styles/muiThemeable';
import {injectIntl, intlShape} from 'react-intl';
import { Activity } from '../../containers/Activity';
import {List, ListItem} from 'material-ui/List';
import Divider from 'material-ui/Divider';
import FontIcon from 'material-ui/FontIcon';
import FloatingActionButton from 'material-ui/FloatingActionButton';
import {withRouter} from 'react-router-dom';
import Avatar from 'material-ui/Avatar';
import { withFirebase } from '../../src';

class Vehicles extends Component {

  componentDidMount() {
    const { watchList}=this.props;
    watchList('companies');
  }

  renderList(companies) {
    const {history} =this.props;

    if(companies===undefined){
      return <div></div>
    }

    return _.map(companies, (row, key) => {

      return <div key={key}>
        <ListItem
          leftAvatar={
            <Avatar
              src={row.photoURL}
              alt="bussines"
              icon={
                <FontIcon className="material-icons">
                  business
                </FontIcon>
              }
            />
          }
          key={key}
          primaryText={row.name}
          secondaryText={row.full_name}
          onTouchTap={()=>{history.push(`/companies/edit/${key}`)}}
          id={key}
        />
        <Divider inset={true}/>
      </div>
    });
  }


  render(){
    const {intl, companies, muiTheme, history} =this.props;

    return (
      <Activity
        isLoading={companies===undefined}
        containerStyle={{overflow:'hidden'}}
        title={intl.formatMessage({id: 'companies'})}>

        <div id="scroller" style={{overflow: 'auto', height: '100%'}}>

          <div style={{overflow: 'none', backgroundColor: muiTheme.palette.convasColor}}>
            <List  id='test' style={{height: '100%'}} ref={(field) => { this.list = field; }}>
              {this.renderList(companies)}
            </List>
          </div>

          <div style={{position: 'fixed', right: 18, zIndex:3, bottom: 18, }}>
            <FloatingActionButton secondary={true} onTouchTap={()=>{history.push(`/companies/create`)}} style={{zIndex:3}}>
            <FontIcon className="material-icons" >add</FontIcon>
          </FloatingActionButton>
        </div>
      </div>
    </Activity>
  );

}

}

Vehicles.propTypes = {
  intl: intlShape.isRequired,
  muiTheme: PropTypes.object.isRequired,
  auth: PropTypes.object.isRequired,
};

const mapStateToProps = (state) => {
  const { auth, browser, lists } = state;

  return {
    companies: lists.companies,
    auth,
    browser,
  };
};


export default connect(
  mapStateToProps,
)(injectIntl(muiThemeable()(withRouter(withFirebase(Vehicles)))));
