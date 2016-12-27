import React, { Component } from 'react';
import { View, ScrollView } from 'react-native';
import axios from 'axios';

import AlbumDetail from './AlbumDetail';

class AlbumList extends Component {
  state = { albums: [] };

  componentWillMount() {
    console.log('1.AlbumList componentWillMount');
    axios.get('https://rallycoding.herokuapp.com/api/music_albums')
      .then(response => this.setState({ albums: response.data }));
  }

  renderAlbums() {
    console.log('1.AlbumList renderAlbums');
    return this.state.albums.map(
      album => <AlbumDetail key={album.title} album={album} />
    );
  }

  render() {
    console.log('1.AlbumList render state: ', this.state);
    return (
      <ScrollView>
        {this.renderAlbums()}
      </ScrollView>
    );
  }
}

export default AlbumList;
