export function checkUri(networkInterface) {
  console.log('1.utils checkUri : ', networkInterface._uri)
  if (!isValidGraphcoolEndpoint(networkInterface._uri)) {
    console.error('Please specify a valid graphcool endpoint url for the network interface in src/root.js')
  }
}

function isValidGraphcoolEndpoint(uri) {
  const lastSlash = uri.lastIndexOf('/')
  const projectId = uri.slice(lastSlash + 1, uri.length)
  console.log('1.utils isValidGraphcoolEndpoint : ', projectId, uri)
  return isCuid(projectId)
}


function isCuid(str) {
  return true
  // return /^c[^\s-]{8,}$/.test(str)
}
