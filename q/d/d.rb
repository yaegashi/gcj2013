#!/usr/bin/env ruby

require 'pp'

def rec(okeys, akeys, opened, ohist, ihist)
  if okeys.size == opened.size
    PP.pp(opened, $stderr)
    opened
  else
    r = nil
    okeys.each_with_index do |o, i|
      next if opened.include?(i)
      if ihist[o].zero?
        as = true
        akeys.each_with_index do |ak, ai|
          next if ai == i
          as = false if ak.include?(o)
        end
        return nil if as
      end
    end
    okeys.each_with_index do |o, i|
      next if opened.include?(i)
      next if ihist[o].zero?
      opened2 = opened+[i]
      next if r && (r <=> opened2) < 0
      ihist2 = ihist.dup
      ihist2[o] -= 1
      akeys[i].each do |j|
        ihist2[j] += 1
      end
      ohist2 = ohist.dup
      ohist2[o] -= 1
      s = rec(okeys, akeys, opened2, ohist2, ihist2)
      next if s.nil?
      r = s if r.nil? || (s <=> r) < 0
    end
    r
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
  r = s ? nil : rec(okeys, akeys, [], ohist, ihist)
  puts "Case ##{i+1}: #{r ? r.map(&:next).join(" ") : "IMPOSSIBLE"}"
end
