#!/usr/bin/python

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.cli import CLI
from mininet.node import RemoteController

class final_topo(Topo):
  def build(self):
    # Examples!
    # Create a host with a default route of the ethernet interface. You'll need to set the
    # default gateway like this for every host you make on this assignment to make sure all 
    # packets are sent out that port. Make sure to change the h# in the defaultRoute area
    # and the MAC address when you add more hosts!
    # h1 = self.addHost('h1',mac='00:00:00:00:00:01',ip='1.1.1.1/24', defaultRoute="h1-eth0")
    # h2 = self.addHost('h2',mac='00:00:00:00:00:02',ip='2.2.2.2/24', defaultRoute="h2-eth0")

    # Create a switch. No changes here from Lab 1.
    # s1 = self.addSwitch('s1')

    # Connect Port 8 on the Switch to Port 0 on Host 1 and Port 9 on the Switch to Port 0 on 
    # Host 2. This is representing the physical port on the switch or host that you are 
    # connecting to.
    #
    # IMPORTANT NOTES: 
    # - On a single device, you can only use each port once! So, on s1, only 1 device can be
    #   plugged in to port 1, only one device can be plugged in to port 2, etc.
    # - On the "host" side of connections, you must make sure to always match the port you 
    #   set as the default route when you created the device above. Usually, this means you 
    #   should plug in to port 0 (since you set the default route to h#-eth0).
    #
    # self.addLink(s1,h1, port1=8, port2=0)
    # self.addLink(s1,h2, port1=9, port2=0)

    h101 = self.addHost('h101',mac='00:00:00:00:00:01',ip='128.114.1.101/24', defaultRoute="h101-eth0")
    h102 = self.addHost('h102',mac='00:00:00:00:00:02',ip='128.114.1.102/24', defaultRoute="h102-eth0")
    h103 = self.addHost('h103',mac='00:00:00:00:00:03',ip='128.114.1.103/24', defaultRoute="h103-eth0")
    h104 = self.addHost('h104',mac='00:00:00:00:00:04',ip='128.114.1.104/24', defaultRoute="h104-eth0")
    h201 = self.addHost('h201',mac='00:00:00:00:00:05',ip='128.114.1.201/24', defaultRoute="h201-eth0")
    h202 = self.addHost('h202',mac='00:00:00:00:00:06',ip='128.114.1.202/24', defaultRoute="h202-eth0")
    h203 = self.addHost('h203',mac='00:00:00:00:00:07',ip='128.114.1.203/24', defaultRoute="h203-eth0")
    h204 = self.addHost('h204',mac='00:00:00:00:00:08',ip='128.114.1.204/24', defaultRoute="h204-eth0")
    h_untrust = self.addHost('h_untrust',mac='00:00:00:00:00:09',ip='108.35.24.113/24', defaultRoute="h_untrust-eth0")
    h_trust = self.addHost('h_trust',mac='00:00:00:00:00:0A',ip='192.47.38.109/24', defaultRoute="h_trust-eth0")
    h_server = self.addHost('h_server',mac='00:00:00:00:00:0B',ip='128.114.3.178/24', defaultRoute="h_server-eth0")

    core = self.addSwitch('core')
    f1s1 = self.addSwitch('f1s1')
    f1s2 = self.addSwitch('f1s2')
    f2s1 = self.addSwitch('f2s1')
    f2s2 = self.addSwitch('f2s2')
    dcs = self.addSwitch('dcs')

    self.addLink(f1s1,h101, port1=8, port2=0)
    self.addLink(f1s1,h102, port1=9, port2=0)
    self.addLink(f1s2,h103, port1=8, port2=0)
    self.addLink(f1s2,h104, port1=9, port2=0)
    self.addLink(f2s1,h201, port1=8, port2=0)
    self.addLink(f2s1,h202, port1=9, port2=0)
    self.addLink(f2s2,h203, port1=8, port2=0)
    self.addLink(f2s2,h204, port1=9, port2=0)
    self.addLink(dcs,h_server, port1=8, port2=0)
    self.addLink(core,f1s1, port1=1, port2=0)
    self.addLink(core,f1s2, port1=2, port2=0)
    self.addLink(core,f2s1, port1=3, port2=0)
    self.addLink(core,f2s2, port1=4, port2=0)
    self.addLink(core,h_untrust, port1=5, port2=0)
    self.addLink(core,h_trust, port1=6, port2=0)
    self.addLink(core,dcs, port1=7, port2=0)

def configure():
  topo = final_topo()
  net = Mininet(topo=topo, controller=RemoteController)
  net.start()

  CLI(net)
  
  net.stop()


if __name__ == '__main__':
  configure()
