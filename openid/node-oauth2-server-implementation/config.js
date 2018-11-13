/**
 * Created by Manjesh on 14-05-2016.
 */

module.exports = {
  sql: {
    database: 'oauth_demo',
    username: 'root',
    password: '',
    dialect: 'mysql', // PostgreSQL, MySQL, MariaDB, SQLite and MSSQL See more: http://docs.sequelizejs.com/en/latest/
    logging: true,
    timezone: '+05:30',
  },
  mongo: {
    uri: 'mongodb://rw:A+20180828@ds133762.mlab.com:33762/oauth2'
  },
  seedDB:false,
  seedMongoDB:false,
  seedDBForce:true,
  db:'mongo' // mongo,sql if you want to use any SQL change dialect above in sql config
}
