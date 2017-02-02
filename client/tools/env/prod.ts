import { EnvConfig } from './env-config.interface';

const ProdConfig: EnvConfig = {
  ENV: 'PROD',
  WS_SERVER_ADDRESS: 'wss://192.168.1.102:1903'
};

export = ProdConfig;

