测试一下git 的一些命令


```
git --help  #查看git的命令
git status #查看远程分支状态
git add .  将代码从工作区增加到本地
git commit -m "提交说明"  提交到本地 
git pull    ---  拉取远程代码
git push -u origin master 
```

从github网站上修改的readme文件

* 学习git 关联远程仓库 

  ```
  git init //把这个目录变成Git可以管理的仓库
  　　git add README.md //文件添加到仓库
  　　git add . //不但可以跟单一文件，还可以跟通配符，更可以跟目录。一个点就把当前目录下所有未追踪的文件全部add了 
  　　git commit -m "first commit" //把文件提交到仓库
  　　git remote add origin git@github.com:wangjiax9/practice.git //关联远程仓库
  　　git push -u origin master //把本地库的所有内容推送到远程库上
  ```

  

* 学习 git 冲突解决方法——定位到冲突文件，删除掉冲突标识符号

* 理解 git 分支


 git checkout
