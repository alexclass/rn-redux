import React, {Component} from 'react';
import _ from 'lodash';
import { connect } from 'react-redux';
import ReactDOM  from 'react-dom';
import firebase from 'firebase';
import PropTypes from 'prop-types';
import muiThemeable from 'material-ui/styles/muiThemeable';
import {injectIntl, intlShape} from 'react-intl';
import { Activity } from '../../containers/Activity';
import { setDialogIsOpen } from '../../store/dialogs/actions';
import {List, ListItem} from 'material-ui/List';
import Divider from 'material-ui/Divider';
import FontIcon from 'material-ui/FontIcon';
import IconButton from 'material-ui/IconButton';
import TextField from 'material-ui/TextField';
import Avatar from 'material-ui/Avatar';
import { green800} from 'material-ui/styles/colors';
import {BottomNavigation} from 'material-ui/BottomNavigation';
import {withRouter} from 'react-router-dom';
import FlatButton from 'material-ui/FlatButton';
import Dialog from 'material-ui/Dialog';
import { withFirebase } from '../../src';

class Tasks extends Component {

  constructor(props) {
    super(props);
    this.name = null;
    this.listEnd=null
    this.new_task_title = null;
    this.state={value: '' }
  }

  scrollToBottom = () => {
    const node = ReactDOM.findDOMNode(this.listEnd);
    node.scrollIntoView({ behavior: "smooth" });
  }

  componentDidUpdate(prevProps, prevState) {

    this.scrollToBottom();

  }

  componentDidMount() {
    const {watchList}=this.props;

    watchList('public_tasks')
    this.scrollToBottom();
  }

  handleKeyDown = (event, onSucces) => {
    if(event.keyCode===13){
      onSucces();
    }
  }

  handleAddTask = () => {
    const { auth, firebaseApp}=this.props;

    const title=this.name.getValue();

    const newTask={
      title: title,
      created: firebase.database.ServerValue.TIMESTAMP ,
      userName: auth.displayName,
      userPhotoURL: auth.photoURL,
      userId: auth.uid,
      completed: false
    }

    this.name.input.value='';

    if(title.length>0){
      firebaseApp.database().ref('public_tasks').push(newTask);
    }



  }

  handleUpdateTask = (key, task) => {
    const { firebaseApp }=this.props;
    firebaseApp.database().ref(`public_tasks/${key}`).update(task);
  }


  userAvatar = (key, task) => {
    const {auth} =this.props;

    return task.completed?
    <Avatar
      onTouchTap={auth.uid===task.userId?()=>{this.handleUpdateTask(key,{...task, completed: !task.completed})}:undefined}
      alt="person"
      icon={<FontIcon className="material-icons" >done</FontIcon>}
      backgroundColor={green800}
    />
    :
    <Avatar
      src={task.userPhotoURL}
      onTouchTap={auth.uid===task.userId?()=>{this.handleUpdateTask(key,{...task, completed: !task.completed})}:undefined}
      alt="person"
      icon={
        <FontIcon className="material-icons">
          person
        </FontIcon>
      }
    />
  }

  renderList(tasks) {
    const { auth, intl, history, browser, setDialogIsOpen} =this.props;

    if(tasks===undefined){
      return <div></div>
    }

    return _.map(tasks, (task, key) => {

      return <div key={key}>

        <ListItem
          key={key}
          onTouchTap={task.userId===auth.uid?()=>{history.push(`/tasks/edit/${key}`)}:undefined}
          primaryText={task.title}
          secondaryText={`${task.userName} ${task.created?intl.formatRelative(new Date(task.created)):undefined}`}
          leftAvatar={this.userAvatar(key, task)}
          rightIconButton={
            task.userId===auth.uid?
            <IconButton
              style={{display:browser.lessThan.medium?'none':undefined}}
              onTouchTap={()=>{setDialogIsOpen('delete_task_from_list', key);}}>
              <FontIcon className="material-icons" color={'red'}>{'delete'}</FontIcon>
            </IconButton>:undefined
          }
          id={key}
        />


        <Divider inset={true}/>
      </div>
    });
  }

  handleClose = () => {
    const { setDialogIsOpen }=this.props;
    setDialogIsOpen('delete_task_from_list', undefined);
  }

  handleDelete = (key) => {
    const {firebaseApp, dialogs} =this.props;
    firebaseApp.database().ref(`public_tasks/${dialogs.delete_task_from_list}`).remove();
    this.handleClose();
  }

  render(){
    const {intl, tasks, muiTheme, dialogs} =this.props;


    const actions = [
      <FlatButton
        label={intl.formatMessage({id: 'cancel'})}
        primary={true}
        onTouchTap={this.handleClose}
      />,
      <FlatButton
        label={intl.formatMessage({id: 'delete'})}
        secondary={true}
        onTouchTap={this.handleDelete}
      />,
    ];

    return (
      <Activity
        isLoading={tasks===undefined}
        containerStyle={{overflow:'hidden'}}
        title={intl.formatMessage({id: 'tasks'})}>

        <div id="scroller" style={{overflow: 'auto', height: '100%'}}>

          <div style={{overflow: 'none', backgroundColor: muiTheme.palette.convasColor}}>
            <List  id='test' style={{height: '100%'}} ref={(field) => { this.list = field; }}>
              {this.renderList(tasks)}
            </List>
            <div style={{ float:"left", clear: "both" }}
              ref={(el) => { this.listEnd = el; }}
            />
          </div>


          {tasks &&
            <BottomNavigation style={{width: '100%'}}>
              <div style={{display:'flex', alignItems: 'center', justifyContent: 'center', padding: 15 }}>
                <TextField
                  id="public_task"
                  fullWidth={true}
                  onKeyDown={(event)=>{this.handleKeyDown(event, this.handleAddTask)}}
                  ref={(field) => { this.name = field; this.name && this.name.focus(); }}
                  type="Text"
                />
                <IconButton
                  onTouchTap={this.handleAddTask}>
                  <FontIcon className="material-icons" color={muiTheme.palette.primary1Color}>send</FontIcon>
                </IconButton>
              </div>
            </BottomNavigation>
          }

          <Dialog
            title={intl.formatMessage({id: 'delete_task_title'})}
            actions={actions}
            modal={false}
            open={dialogs.delete_task_from_list!==undefined}
            onRequestClose={this.handleClose}>
            {intl.formatMessage({id: 'delete_task_message'})}
          </Dialog>


        </div>

      </Activity>
    );

  }

}

Tasks.propTypes = {
  intl: intlShape.isRequired,
  muiTheme: PropTypes.object.isRequired,
  auth: PropTypes.object.isRequired,
};

const mapStateToProps = (state) => {
  const { lists, auth, browser, dialogs } = state;

  return {
    tasks: lists.public_tasks,
    auth,
    browser,
    dialogs
  };
};




export default connect(
  mapStateToProps,
  { setDialogIsOpen }
)(injectIntl(muiThemeable()(withRouter(withFirebase(Tasks)))));
