#!/usr/bin/env ruby

require 'pp'

def reachable(okeys, akeys, opened, ihist)
  ihist2 = ihist.dup
  opened2 = opened.dup
  count = 0
  while opened2.size < okeys.size
    openable = []
    ihist2.each do |i, n|
      next if n.zero?
      okeys.each_with_index do |o, j|
        openable += [j] if !opened2.include?(j) && o == i
      end
      pp [i,n]
    end
    return false if openable.empty? 
    opened2 += openable
    openable.each do |n|
      akeys[n].each do |i|
        ihist2[i] += 1
      end
    end
  end
  return true
end


def rec(okeys, akeys, opened, ihist)
  if okeys.size == opened.size
    PP.pp(opened, $stderr)
    opened
  else
    return nil unless reachable(okeys, akeys, opened, ihist)
    okeys.each_with_index do |o, i|
      next if opened.include?(i)
      next if ihist[o].zero?
      opened2 = opened + [i]
      ihist2 = ihist.dup
      ihist2[o] -= 1
      akeys[i].each do |j|
        ihist2[j] += 1
      end
      s = rec(okeys, akeys, opened2, ihist2)
      return s unless s.nil?
    end
    PP.pp(opened, $stderr)
    nil
  end
end

t = gets.to_i

t.times do |i|
  okeys = []
  akeys = []
  ohist = {}
  ihist = {}
  ohist.default = 0
  ihist.default = 0
  k, n = gets.chomp.split.map(&:to_i)
  ikeys = gets.chomp.split.map(&:to_i)
  ikeys.each do |j|
    ihist[j] += 1
  end
  ahist = ihist.dup
  n.times do
    ak = gets.chomp.split.map(&:to_i)
    okeys << ak.shift
    ak.shift
    akeys << ak
    ak.each do |j|
      ahist[j] += 1
    end
  end
  okeys.each do |j|
    ohist[j] += 1
  end
  PP.pp([okeys, akeys, ohist, ihist, ahist], $stderr)
  s = false
  ohist.each do |i, o|
    s = true if o > ahist[i]
  end
  r = s ? nil : rec(okeys, akeys, [], ihist)
  puts "Case ##{i+1}: #{r ? r.map(&:next).join(" ") : "IMPOSSIBLE"}"
end
